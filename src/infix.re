module Option = {
  let (>>|) = (x, f) =>
    switch (x) {
    | None => None
    | Some(y) => Some(f(y))
    };
  let (<|>) = (a, b) =>
    switch (a) {
    | None => b
    | Some(x) => x
    };
};

module Result = {
  let (>>|): (result('a, 'b), 'a => 'c) => result('c, 'b) =
    (x, f) =>
      switch (x) {
      | Ok(y) => Ok(f(y))
      | err => err
      };
  let (<|>): (result('a, 'b), 'a) => 'a =
    (a, b) =>
      switch (a) {
      | Ok(x) => x
      | _ => b
      };
};
