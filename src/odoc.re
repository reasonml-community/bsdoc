module Bin = {
  let odoc = Os.run("odoc");

  let support_files = out_dir =>
    odoc(["support-files", "--output-dir", out_dir]) |> ignore;

  let include_one = (list, lib_dir) => ["-I", lib_dir, ...list];
  let include_all = List.fold_left(include_one, []);

  let compile = (lib_dirs, pkg_name, file_name) =>
    [["compile"], include_all(lib_dirs), ["--pkg=" ++ pkg_name, file_name]]
    |> List.concat
    |> odoc
    |> ignore;

  let compile_mld = (lib_dirs, out_file, pkg_name, file_name) =>
    [
      ["compile"],
      include_all(lib_dirs),
      ["--pkg=" ++ pkg_name, "-o", out_file, file_name],
    ]
    |> List.concat
    |> odoc
    |> ignore;

  let html = (lib_dirs, out_dir, file_name) =>
    [
      ["html"],
      include_all(lib_dirs),
      ["-o", out_dir, "--syntax=re", "--semantic-uris", file_name],
    ]
    |> List.concat
    |> odoc
    |> ignore;
};

let support_files = Bin.support_files;

let swap_extension = (ext, path) => Filename.(path |> chop_extension) ++ ext;

let as_odoc = swap_extension(".odoc");
let as_html = swap_extension(".html");

let cmti_to_odoc = (lib_dirs, pkg_name, cmti) => {
  let odoc = as_odoc(cmti);
  Logs.debug(m => m("Compiling %s to %s...", cmti, odoc));
  Bin.compile(lib_dirs, pkg_name, cmti);
  odoc;
};

let mld_to_odoc = (lib_dirs, _src_dir, pkg_name, mld) => {
  let odoc = "page-" ++ as_odoc(mld);
  Logs.debug(m => m("Compiling %s to %s...", mld, odoc));
  Bin.compile_mld(
    lib_dirs,
    /* We know there's at least a [lib/bs] directory for BuckleScript
       output */
    Filename.concat(List.hd(lib_dirs), odoc),
    pkg_name,
    mld,
  );
  odoc;
};

let odoc_to_html = (lib_dirs, out_dir, odoc) => {
  let html = as_html(odoc);
  Logs.debug(m => m("Compiling %s to %s...", odoc, html));
  Bin.html(lib_dirs, out_dir, odoc);
  html;
};
