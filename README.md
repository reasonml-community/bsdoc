# bsdoc
> Documentation Generation for BuckleScript projects

Read more in the docs: [BsDoc](https://ostera.github.io/bsdoc)

## Usage

Install in your project using `npm` or `yarn`:

```sh
$ yarn add bsdoc@6.0.0-alpha
yarn add v1.12.3
[1/4] 🔍  Resolving packages...
[2/4] 🚚  Fetching packages...
[3/4] 🔗  Linking dependencies...
[4/4] 📃  Building fresh packages...
success Saved lockfile.
warning example@0.1.0: No license field
warning "bsdoc" is already in "devDependencies". Please remove existing entry first before adding it to "dependencies".
success Saved 1 new dependency.
info Direct dependencies
└─ bsdoc@6.0.0-alpha
info All dependencies
└─ bsdoc@6.0.0-alpha
✨  Done in 6.68s.
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

If you haven't installed Esy yet, follow the isntructions in their web site:
https://esy.sh

After you have done that, you need only run `esy build` to get the project
bootstrapped.
