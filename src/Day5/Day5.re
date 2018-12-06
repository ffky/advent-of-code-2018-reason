let parse = input => input |> Js.String.replaceByRe([%re "/\\r?\\n?/g"], "");

let charList = l => l->Js.String.split("", _)->Belt.List.fromArray;

let isSameLetter = (a, b) =>
  Js.String.toUpperCase(a) == Js.String.toUpperCase(b);

let isLowerCase = x =>
  x == Js.String.toLowerCase(x) && x != Js.String.toUpperCase(x);

let isUpperCase = x =>
  x == Js.String.toUpperCase(x) && x != Js.String.toLowerCase(x);

let shouldZap = (a, b) =>
  isSameLetter(a, b)
  && (isLowerCase(a) && isUpperCase(b) || isLowerCase(b) && isUpperCase(a));

let process = l => {
  let rec aux = (l1, l2) =>
    switch (l1) {
    | [] => l2
    | [h, ...t] =>
      switch (l2) {
      | [] => aux(t, [h])
      | [h2] =>
        if (shouldZap(h, h2)) {
          aux(t, []);
        } else {
          aux(t, [h, h2]);
        }
      | [h2, ...t2] =>
        if (shouldZap(h, h2)) {
          aux(t, t2);
        } else {
          aux(t, [h, h2, ...t2]);
        }
      }
    };
  aux(l, []);
};

let part1 = input => parse(input)->charList->process->Belt.List.length;

let letters = "abcdefghijklmnopqrstuvwxyz";

let remove = (letterList, letter) =>
  letterList->Belt.List.keep(letter2 =>
    letter2 != letter && letter2 != Js.String.toUpperCase(letter)
  );

let part2 = input => {
  let input = parse(input)->charList;
  letters
  ->charList
  ->Belt.List.reduce(
      None,
      (acc, letter) => {
        let count = input->remove(letter)->process->Belt.List.length;
        switch (acc) {
        | None => Some(count)
        | Some(lastCount) =>
          count < lastCount ? Some(count) : Some(lastCount)
        };
      },
    )
  ->Belt.Option.getExn;
};
