const pluginNavigation = require("@11ty/eleventy-navigation");
const lazyImagesPlugin = require("eleventy-plugin-lazyimages");
const sitemap = require("@quasibit/eleventy-plugin-sitemap");

module.exports = function (eleventyConfig) {
  eleventyConfig.addPassthroughCopy("assets");
  eleventyConfig.addPassthroughCopy("css");
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

  return {
    markdownTemplateEngine: "njk"
  };
};
