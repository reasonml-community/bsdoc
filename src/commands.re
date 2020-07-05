let support_files = (_flags, out_dir) => {
  Logs.info(m => m("Copying support files (CSS, JS) into %s", out_dir));

  Logs.debug(m => m("Making sure output dir %s exists...", out_dir));
  Os.mkdirp(out_dir) |> ignore;

  Odoc.support_files(out_dir) |> ignore;
  Logs.info(m => m("Done ✅"));
};

let build = (_flags, out_dir, pkg_name, src_dir, lib_dir) => {
  let package = Bucklescript.package(pkg_name, src_dir, lib_dir);
  let lib_dirs = Os.subdirs(lib_dir);

  Logs.info(m =>
    m("Compiling documentation for package \"%s\"...", pkg_name)
  );

  Logs.debug(m => m("Making sure output dir \"%s\" exists...", out_dir));
  Os.mkdirp(out_dir) |> ignore;

  Logs.debug(m => m("Looking for .cmti files in %s", lib_dir));
  Logs.debug(m => m("Compiling .cmti files into .odoc files..."));
  let cmti_odocs =
    package.cmtis |> List.map(Odoc.cmti_to_odoc(lib_dirs, pkg_name));
  Logs.debug(m => m("Done"));

  Logs.debug(m => m("Looking for .mld files in %s", src_dir));
  Logs.debug(m => m("Compiling .mld files into .odoc files..."));
  let mld_odocs =
    List.map(Odoc.mld_to_odoc(lib_dirs, src_dir, pkg_name), package.mlds);
  Logs.debug(m => m("Done"));

  Logs.info(m => m("Generating .html files..."));
  let odocs = cmti_odocs @ mld_odocs;
  let _htmls = List.map(Odoc.odoc_to_html(lib_dirs, out_dir), odocs);
  Logs.info(m => m("Done"));
};
