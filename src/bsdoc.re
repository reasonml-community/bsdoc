open Cmdliner;

let began_at = Unix.gettimeofday();

type verbosity =
  | Quiet
  | Normal
  | Verbose;

module Shared_optss = {
  let setup_logger = (debug, verbosity) => {
    Fmt_tty.setup_std_outputs();
    Logs.set_reporter(Logs_fmt.reporter());
    let verbosity' =
      switch (verbosity) {
      | Quiet => None
      | Normal => Some(Logs.App)
      | Verbose => debug ? Some(Logs.Debug) : Some(Logs.Info)
      };
    Logs.set_level(verbosity');
  };
  let help = [
    `S(Manpage.s_common_options),
    `P("These options are common to all commands."),
    `S("MORE HELP"),
    `P("Use `$(mname) $(i,COMMAND) --help' for help on a single command."),
    `Noblank,
    `S(Manpage.s_bugs),
    `P("Check bug reports at https://github.com/ostera/bsdoc."),
  ];
  let flags = {
    let docs = Manpage.s_common_options;
    let debug = {
      let doc = "Give only debug output.";
      Arg.(value & flag & info(["debug"], ~docs, ~doc));
    };

    let verb = {
      let doc = "Suppress informational output.";
      let quiet = (Quiet, Arg.info(["q", "quiet"], ~docs, ~doc));
      let doc = "Give verbose output.";
      let verbose = (Verbose, Arg.info(["v", "verbose"], ~docs, ~doc));
      Arg.(last & vflag_all([Normal], [quiet, verbose]));
    };

    Term.(const(setup_logger) $ debug $ verb);
  };
};

module Support_files = {
  let cmd = {
    let out_dir = {
      let doc = "Output directory of the generated documentation";
      Arg.(
        value
        & opt(file, "./docs")
        & info(["o", "output-dir"], ~docv="DIR", ~doc)
      );
    };

    let doc = {j|Copy the support files (e.g. default theme, JavaScript files)
to the output directory.|j};
    let exits = Term.default_exits;
    let man = [
      `S(Manpage.s_description),
      `P(
        {j|Copies the support files for the generated documentation. This
includes a default stylesheet that can be further customized later on and a small
amount of Javascript to support syntax highlightning.|j},
      ),
      `Blocks(Shared_optss.help),
    ];

    (
      Term.(const(Commands.support_files) $ Shared_optss.flags $ out_dir),
      Term.info(
        "support-files",
        ~doc,
        ~sdocs=Manpage.s_common_options,
        ~exits,
        ~man,
      ),
    );
  };
};

module Build = {
  let cmd = {
    let pkg_name = {
      let doc = "The name of your package (e.g., Commands)";
      Arg.(
        required
        & pos(~rev=true, 0, some(string), None)
        & info([], ~docv="NAME", ~doc)
      );
    };

    let lib_dir = {
      let doc = "Compilation directory where your .cmt/.cmti files live";
      Arg.(
        value
        & opt(file, "./lib/bs")
        & info(["l", "lib-dir"], ~docv="DIR", ~doc)
      );
    };

    let src_dir = {
      let doc = "Source directory where your .mld files live";
      Arg.(
        value
        & opt(file, "./src")
        & info(["s", "source-dir"], ~docv="DIR", ~doc)
      );
    };

    let out_dir = {
      let doc = "Output directory of the generated documentation";
      Arg.(
        value
        & opt(file, "./docs")
        & info(["o", "output-dir"], ~docv="DIR", ~doc)
      );
    };

    let doc = "generate documentation for a BuckleScript project";
    let exits = Term.default_exits;
    let man = [
      `S(Manpage.s_description),
      `P(
        {j|Generates documentation for a BuckleScript project by orchestrating a
global odoc installation.|j},
      ),
      `Blocks(Shared_optss.help),
    ];

    (
      Term.(
        const(Commands.build)
        $ Shared_optss.flags
        $ out_dir
        $ pkg_name
        $ src_dir
        $ lib_dir
      ),
      Term.info("build", ~doc, ~sdocs=Manpage.s_common_options, ~exits, ~man),
    );
  };
};

let default_cmd = {
  let doc = "Documentation Generator for BuckleScript projects.";
  let sdocs = Manpage.s_common_options;
  let exits = Term.default_exits;
  let man = Shared_optss.help;
  (
    Term.(ret(const(_ => `Help((`Pager, None))) $ Shared_optss.flags)),
    Term.info("bsdoc", ~version="v6.0.3-alpha", ~doc, ~sdocs, ~exits, ~man),
  );
};

let cmds = [Build.cmd, Support_files.cmd];

Term.(exit @@ eval_choice(default_cmd, cmds));
