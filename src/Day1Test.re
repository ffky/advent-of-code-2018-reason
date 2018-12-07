Jest.describe("part 1", () => {
  Jest.test("parses input", () => {
    let input = "+1\n-2\n+1";
    Day1.parse(input)->Jest.expect->Jest.Expect.toEqual([1, (-2), 1]);
    Js.undefined;
  });

  Jest.test("parses out last newline blank row", () => {
    let input = "+1\n-2\n+1\n";
    Day1.parse(input)->Jest.expect->Jest.Expect.toEqual([1, (-2), 1]);
    Js.undefined;
  });

  Jest.test("example 1", () => {
    Day1.part1([1, (-2), 3, 1])->Jest.expect->Jest.Expect.toBe(3);
    Js.undefined;
  });

  Jest.test("example 2", () => {
    Day1.part1([1, 1, 1])->Jest.expect->Jest.Expect.toBe(3);
    Js.undefined;
  });

  Jest.test("example 3", () => {
    Day1.part1([1, 1, (-2)])->Jest.expect->Jest.Expect.toBe(0);
    Js.undefined;
  });

  Jest.test("example 4", () => {
    Day1.part1([(-1), (-2), (-3)])->Jest.expect->Jest.Expect.toBe(-6);
    Js.undefined;
  });

  Js.undefined;
});

Jest.describe("part2", () => {
  Jest.test("example 1", () => {
    Day1.part2([1, (-2), 3, 1])->Jest.expect->Jest.Expect.toBe(2);
    Js.undefined;
  });

  Jest.test("example 2", () => {
    Day1.part2([1, -1])
    ->Jest.expect
    ->Jest.Expect.toBe(0);
    Js.undefined;
  });

  Jest.test("example 3", () => {
    Day1.part2([3, 3, 4, (-2) - 4])
    ->Jest.expect
    ->Jest.Expect.toBe(10);
    Js.undefined;
  });

  Jest.test("example 4", () => {
    Day1.part2([(-6), 3, 8, 5, (-6)])
    ->Jest.expect
    ->Jest.Expect.toBe(5);
    Js.undefined;
  });

  Jest.test("example 5", () => {
    Day1.part2([7, 7, (-2), (-7), (-4)])
    ->Jest.expect
    ->Jest.Expect.toBe(14);
    Js.undefined;
  });

  Js.undefined;
});
