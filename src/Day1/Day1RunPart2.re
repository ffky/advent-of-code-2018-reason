let inputPath = Process.argv->Belt.Array.getExn(2);

let data =
  Fs.readFileSync(inputPath, Fs.ReadFile.Options.t(~encoding="utf-8"));

Day1.parse(data)->Day1.duplicateSum->Js.log;
