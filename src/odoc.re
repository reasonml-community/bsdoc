module Bin = {
  let odoc = Os.run("odoc");

  let support_files = out_dir =>
    odoc(["support-files", "--output-dir", out_dir]) |> ignore;

  let compile = (lib_dir, pkg_name, file_name) =>
    odoc(["compile", "-I", lib_dir, "--pkg=" ++ pkg_name, file_name])
    |> ignore;

  let compile_mld = (lib_dir, out_file, pkg_name, file_name) =>
    odoc([
      "compile",
      "-I",
      lib_dir,
      "--pkg=" ++ pkg_name,
      "-o",
      out_file,
      file_name,
    ])
    |> ignore;

  let html = (lib_dir, out_dir, file_name) =>
    odoc([
      "html",
      "-I",
      lib_dir,
      "-o",
      out_dir,
      "--syntax=re",
      "--semantic-uris",
      file_name,
    ])
    |> ignore;
};

let support_files = Bin.support_files;

let swap_extension = (ext, path) => Filename.(path |> chop_extension) ++ ext;

let as_odoc = swap_extension(".odoc");
let as_html = swap_extension(".html");

let cmti_to_odoc = (lib_dir, pkg_name, cmti) => {
  let odoc = as_odoc(cmti);
  Logs.debug(m => m("Compiling %s to %s...", cmti, odoc));
  Bin.compile(lib_dir, pkg_name, cmti);
  odoc;
};

let mld_to_odoc = (lib_dir, _src_dir, pkg_name, mld) => {
  let odoc = "page-" ++ as_odoc(mld);
  Logs.debug(m => m("Compiling %s to %s...", mld, odoc));
  Bin.compile_mld(lib_dir, Filename.concat(lib_dir, odoc), pkg_name, mld);
  odoc;
};

let odoc_to_html = (lib_dir, out_dir, odoc) => {
  let html = as_html(odoc);
  Logs.debug(m => m("Compiling %s to %s...", odoc, html));
  Bin.html(lib_dir, out_dir, odoc);
  html;
};
