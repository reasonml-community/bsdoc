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
      |> Bos.OS.Dir.contents
      |> Rresult.R.ignore_error(~use=_ => [])
      |> List.map(p' => {
           let is_folder =
             Bos.OS.Dir.exists(p') |> Rresult.R.ignore_error(~use=_ => false);
           switch (is_folder) {
           | true => read(p')
           | _ => [p']
           };
         })
      |> List.concat;
    };
  read(path);
};

let mkdirp = path => Bos.OS.Dir.create(~path=true, path |> Fpath.v);
