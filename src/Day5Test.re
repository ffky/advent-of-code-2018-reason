let input = {|dabAcCaCBAcCcaDA
|};

Jest.test("parse", () => {
  Day5.parse(input)->Jest.expect->Jest.Expect.toBe("dabAcCaCBAcCcaDA");
  Js.undefined;
});

Jest.test("process", () => {
  Day5.parse(input)
  ->Day5.charList
  ->Day5.process
  ->Belt.List.reverse
  ->Belt.List.toArray
  ->Js.Array.joinWith("", _)
  ->Jest.expect
  ->Jest.Expect.toEqual("dabCBAcaDA");
  Js.undefined;
});

Jest.test("process another one", () => {
  let input2 = {|zJNnfFFfhsSlqQRrLHKSskoOgGNzZnyiIYuUu
|};
  Day5.parse(input2)
  ->Day5.charList
  ->Day5.process
  ->Belt.List.reverse
  ->Belt.List.toArray
  ->Js.Array.joinWith("", _)
  ->Jest.expect
  ->Jest.Expect.toEqual("zJu");
  Js.undefined;
});

Jest.test("should zap", () => {
  Day5.shouldZap("c", "C")->Jest.expect->Jest.Expect.toBe(true);
  Js.undefined;
});

Jest.test("part 1", () => {
  Day5.part1(input)->Jest.expect->Jest.Expect.toBe(10);
  Js.undefined;
});

Jest.test("part 2", () => {
  Day5.part2(input)->Jest.expect->Jest.Expect.toBe(4);
  Js.undefined;
});
