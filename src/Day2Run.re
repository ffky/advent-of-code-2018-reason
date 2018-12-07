let dirname = [%bs.node __dirname];
let dirname = Belt.Option.getExn(dirname);
let input = Node.Fs.readFileAsUtf8Sync(dirname ++ "/Day2Input")->Day2.parse;
Day2.part1(input)->Js.log;
Day2.part2(input)->Js.log;
