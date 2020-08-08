module.exports = function (eleventyConfig) {
  eleventyConfig.addPassthroughCopy("svg");
  eleventyConfig.addPassthroughCopy("img");
  eleventyConfig.addPassthroughCopy("css");
};
