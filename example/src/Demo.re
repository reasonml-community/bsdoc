type t =
  /* [Some] constructs a value of type [t] */
  | Some
  /* [Type] constructs a value of type [t] */
  | Type;

let run = () => {
  Js.log("Hello, BuckleScript and Reason!");
};
