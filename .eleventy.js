const lazyImagesPlugin = require("eleventy-plugin-lazyimages");
const sitemap = require("@quasibit/eleventy-plugin-sitemap");
const syntaxHighlight = require("@11ty/eleventy-plugin-syntaxhighlight");
const readingTime = require("eleventy-plugin-reading-time");
const pluginRss = require("@11ty/eleventy-plugin-rss");
const util = require("util");

const { DateTime } = require("luxon");

module.exports = function (eleventyConfig) {
  const siteUrl = "https://siddhant.codes";

  eleventyConfig.addPassthroughCopy("src/assets");
  eleventyConfig.addPassthroughCopy("src/css");
  eleventyConfig.addPassthroughCopy("src/notes");
  eleventyConfig.ignores.add("src/notes/**");


  eleventyConfig.addPlugin(syntaxHighlight);
  eleventyConfig.addPlugin(lazyImagesPlugin, {
    imgSelector: ".post-content img",
    scriptSrc: "/assets/lazysizes.min.js",
  });
  eleventyConfig.addPlugin(sitemap, {
    sitemap: {
      hostname: "https://www.siddhant.codes",
    },
  });
  eleventyConfig.addPlugin(readingTime);
  eleventyConfig.addPlugin(pluginRss);

  eleventyConfig.addFilter("readableDate", (dateObj) => {
    return DateTime.fromJSDate(dateObj, { zone: "utc" }).toFormat(
      "dd LLLL yyyy"
    );
  });

  eleventyConfig.addFilter('console', function(value) {
        return util.inspect(value);
  });

  eleventyConfig.addFilter("getog", (title = "") => {
    if (!title) {
      return "https://avatars0.githubusercontent.com/u/36407043?s=460&u=d69d346035fb6a4ddfa2f47f18399d5b205f4ed2&v=4";
    }

    return `${siteUrl}/assets/og/${title
      .toLowerCase()
      .replace(/ /g, "_")}.png`;
  });

  return {
    markdownTemplateEngine: "njk",
    dir: {
      input: "src",
    },
  };
};
