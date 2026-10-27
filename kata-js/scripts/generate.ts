// Writes the TS stubs for a day and points the @code/* alias at it.
//   bun scripts/generate.ts day3 BubbleSort LRU ...   (called by `just generate`)
import fs from "node:fs";
import path from "node:path";
import dsa, { type Kata, type Method, type Property } from "./dsa";

const root = path.join(import.meta.dir, "..");
const [day_name, ...names] = process.argv.slice(2);

if (!day_name || !/^day\d+$/.test(day_name) || names.length === 0) {
    console.error("usage: bun scripts/generate.ts dayN Kata1 Kata2 ...");
    process.exit(1);
}
for (const name of names) {
    if (!dsa[name]) {
        console.error(`algorithm ${name} could not be found`);
        process.exit(1);
    }
}

function generate_method(method: Method): string {
    return `${method.name}(${method.args || ""}): ${method.return || "void"} {

}`;
}

function generate_property(prop: Property): string {
    return `${prop.scope} ${prop.name}: ${prop.type};`;
}

function ts_source(name: string, item: Kata): string {
    if (item.type === "fn") {
        return `export default function ${item.fn}${item.generic || ""}(${item.args}): ${item.return} {

}`;
    }

    return `export default class ${name}${item.generic || ""} {
    ${(item.properties || []).map(generate_property).join("\n    ")}

    ${(item.getters || [])
        .map((g) => `get ${g.name}(): ${g.return} {\n    return this.${g.prop_name};\n}`)
        .join("\n    ")}

    constructor() {
    }

    ${(item.methods || []).map(generate_method).join("\n    ")}
}`;
}

const dir = path.join(root, "src", day_name);
fs.mkdirSync(dir, { recursive: true });
for (const name of names) {
    fs.writeFileSync(path.join(dir, `${name}.ts`), ts_source(name, dsa[name]));
}

const tsconfig_path = path.join(root, "tsconfig.json");
const tsconfig = JSON.parse(fs.readFileSync(tsconfig_path, "utf8"));
tsconfig.compilerOptions.paths["@code/*"] = [`${day_name}/*`];
fs.writeFileSync(tsconfig_path, JSON.stringify(tsconfig, null, 4) + "\n");
