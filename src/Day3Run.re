let dirname = [%bs.node __dirname];
let dirname = Belt.Option.getExn(dirname);
let input = Node.Fs.readFileAsUtf8Sync(dirname ++ "/Day3Input")->Day3.parse;
Day3.part1(input)->Js.log;
Day3.part2(input)->Js.log;
