open Common;
open Logger;

let support_files = (flags, out_dir) => {
  info({j|Copying support files (CSS, JS) into $out_dir|j});
  Odoc.support_files(out_dir);
  info({j|Done ✅|j});
};

let build = (flags, out_dir) => {
  let pkg_name = "ReActor";
  let src_dir = "./src";
  let lib_dir = "./lib/bs/src";
  let out_dir = "./docs";

  let package = BuckleScript.package(pkg_name, src_dir, lib_dir);

  info({j|Compiling documentation for package "$pkg_name"...|j});

  debug({j|Looking for .cmti files in $lib_dir|j});
  debug({j|Compiling .cmti files into .odoc files...|j});
  let cmti_odocs =
    List.map(Odoc.cmti_to_odoc(lib_dir, pkg_name), package.cmtis);
  debug({j|Done ✅|j});

  debug({j|Looking for .mld files in $src_dir|j});
  debug({j|Compiling .mld files into .odoc files...|j});
  let mld_odocs =
    List.map(Odoc.mld_to_odoc(lib_dir, src_dir, pkg_name), package.mlds);
  debug({j|Done ✅|j});

  info({j|Generating .html files...|j});
  let odocs = cmti_odocs @ mld_odocs;
  let htmls = List.map(Odoc.odoc_to_html(lib_dir, out_dir), odocs);
  info({j|Done ✅|j});
};
