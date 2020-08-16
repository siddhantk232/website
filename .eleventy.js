const pluginNavigation = require("@11ty/eleventy-navigation");
const lazyImagesPlugin = require("eleventy-plugin-lazyimages");
const sitemap = require("@quasibit/eleventy-plugin-sitemap");
const syntaxHighlight = require("@11ty/eleventy-plugin-syntaxhighlight");
const readingTime = require("eleventy-plugin-reading-time");

const { DateTime } = require("luxon");

module.exports = function (eleventyConfig) {
  eleventyConfig.addPassthroughCopy("assets");
  eleventyConfig.addPassthroughCopy("css");

  eleventyConfig.addPlugin(syntaxHighlight);
  eleventyConfig.addPlugin(lazyImagesPlugin, {
    imgSelector: ".post-content img",
    scriptSrc: "/assets/lazysizes.min.js"
  });
  eleventyConfig.addPlugin(pluginNavigation);
  eleventyConfig.addPlugin(sitemap, {
    sitemap: {
      hostname: "https://www.siddhant.codes"
    }
  });
  eleventyConfig.addPlugin(readingTime);

  eleventyConfig.addFilter("htmlDateString", dateObj => {
    return DateTime.fromJSDate(dateObj, { zone: "utc" }).toFormat(
      "dd LLLL yyyy"
    );
  });

  return {
    markdownTemplateEngine: "njk"
  };
};
