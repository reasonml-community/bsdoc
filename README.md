# bsdoc

> Documentation Generation for BuckleScript projects

[![Build Status](https://dev.azure.com/yawaramin/bsdoc/_apis/build/status/yawaramin.bsdoc?branchName=master)](https://dev.azure.com/yawaramin/bsdoc/_build/latest?definitionId=5?branchName=master)

Read more in the docs: [BsDoc](https://reasonml-community.github.io/bsdoc)

## Usage

Install in your project using `npm` or `yarn`:

```sh
$ yarn add bsdoc
```

And whenever you want to generate your docs you can run:

```sh
# Build your docs!
MyProject $ yarn run bsdoc build MyProject
yarn run v1.12.3
$ ./node_modules/.bin/bsdoc build MyProject
info: Compiling documentation for package "MyProject"...
info: Generating .html files...
info: Done ✅
✨  Done in 0.58s.
```

Additionally, to install the support files (default CSS and Javascript), you
can run:

```sh
# Create the support files
MyProject $ yarn run bsdoc support-files
yarn run v1.12.3
$ ./node_modules/.bin/bsdoc support-files
info: Copying support files (CSS, JS) into ./docs
info: Done ✅
✨  Done in 0.53s.
```

## Contributing

`bsdoc` is developed as a Native Reason project, and is only possible thanks to
`esy`, `dune`, and, naturally, `odoc`.

If you haven't installed Esy yet, follow the instructions in their web site:
https://esy.sh

After you have done that, you need only run `esy build` to get the project
bootstrapped.

## Installing on Linux/Windows

Unfortunately I haven't gotten around publishing `bsdoc` for Linux/Windows, but if you have `npm` installed you can run:

```sh
$ esy build
$ esy npm-release
```

And that'll get you an npm package that you can then install locally (or globally) in any of your projects. Be mindful that it'll only work for `bs-platform@6`+ projects!
