let parse = input =>
  Js.String.split("\n", input)
  ->Belt.List.fromArray
  ->Belt.List.keep(x => x != "")
  ->Belt.List.map(row => {
      let matches = row |> Js.String.match([%re "/(\\d), (\\d)/"]);
      switch (matches) {
      | None => Js.Exn.raiseError("no matches")
      | Some(matches) =>
        let get = index => matches->Belt.Array.getExn(index)->int_of_string;
        (get(1), get(2));
      };
    });
