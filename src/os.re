module Dir = Bos.OS.Dir;

let run = (cmd, args) => {
  let full_cmd = Bos.(List.fold_left(Cmd.(%), Cmd.v(cmd), args));
  Logs.debug(m => m("Executing %s", full_cmd |> Bos.Cmd.to_string));
  Rresult.R.(
    Bos.OS.Cmd.run_status(full_cmd)
    >>| (
      fun
      | `Exited(code) => code == 0
      | `Signaled(_) => false
    )
    |> Rresult.R.ignore_error(~use=_ => false)
  );
};

let readdir = path => {
  let path = path |> Fpath.v;
  let rec read: Fpath.t => list(Fpath.t) =
    p => {
      p
      |> Dir.contents
      |> Rresult.R.ignore_error(~use=_ => [])
      |> List.map(p' => {
           let is_folder =
             Dir.exists(p') |> Rresult.R.ignore_error(~use=_ => false);
           switch (is_folder) {
           | true => read(p')
           | _ => [p']
           };
         })
      |> List.concat;
    };
  read(path);
};

/* Not tail-recursive, but there should probably be less than 10,000
   files in the project... (I hope) */
let rec subdirs = path =>
  switch (Dir.exists(path)) {
  | Ok(true) => [
      path,
      ...switch (Dir.contents(path)) {
         | Ok(paths) => paths |> List.map(subdirs) |> List.concat
         | Error(_) => []
         },
    ]
  | _ => []
  };

let subdirs = dir => dir |> Fpath.v |> subdirs |> List.map(Fpath.to_string);

let mkdirp = path => Bos.OS.Dir.create(~path=true, path |> Fpath.v);
