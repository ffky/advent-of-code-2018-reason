let inputPath = Node.Process.argv->Belt.Array.getExn(2);
let data = Node.Fs.readFileAsUtf8Sync(inputPath);
Day3.parse(data)->Day3.part2->Js.log;
