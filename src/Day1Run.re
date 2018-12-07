let dirname = [%bs.node __dirname];
let dirname = Belt.Option.getExn(dirname);
let input = Node.Fs.readFileAsUtf8Sync(dirname ++ "/Day1Input")->Day1.parse;
Day1.part1(input)->Js.log;
Day1.part2(input)->Js.log;
