module ReadFile = {
  module Options = {
    [@bs.deriving abstract]
    type t = {encoding: string};
  };
};

[@bs.module "fs"]
external readFileSync: (string, ReadFile.Options.t) => string = "";
