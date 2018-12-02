/* Need [@bs.uncurry] so the JS output calls with no arguments for the
   function */
[@bs.val]
external describe:
  (string, [@bs.uncurry] (unit => Js.undefined(unit))) => unit =
  "";

[@bs.val]
external test: (string, [@bs.uncurry] (unit => Js.undefined(unit))) => unit =
  "";

module Expect = {
  type t;
  [@bs.send] external toBe: (t, 'a) => unit = "";
  [@bs.send] external toEqual: (t, 'a) => unit = "";
};

[@bs.val] external expect: 'a => Expect.t = "";
