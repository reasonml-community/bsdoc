# bsdoc
> Lets you use `odoc` in your BuckleScript projects.

Status: __alpha__.

Read more in the docs: [BsDoc](https://ostera.github.io/bsdoc)

### Getting Started

```sh
# Go into your project
$ cd MyProject
MyProject $ yarn add bsdoc

# Create the support files
MyProject $ yarn run bsdoc support-files
yarn run v1.12.3
$ ./node_modules/.bin/bsdoc support-files
info: Copying support files (CSS, JS) into ./docs
info: Done ✅
✨  Done in 0.53s.

# Build your docs!
MyProject $ yarn run bsdoc build MyProject
yarn run v1.12.3
$ ./node_modules/.bin/bsdoc build MyProject
info: Compiling documentation for package "MyProject"...
info: Generating .html files...
info: Done ✅
✨  Done in 0.58s.
```
