module Option = {
  let (|>>) = (x, f) =>
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
