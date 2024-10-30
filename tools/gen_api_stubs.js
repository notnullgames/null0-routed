// this will generate stubs for each host function

import fs from 'fs/promises'
import { glob } from 'glob'
import YAML from 'yaml'

for (const y of await glob('api/**/*.yml')) {
  const api = YAML.parse(await fs.readFile(y, 'utf8'))
  const [, catName] = /^api\/(.+)\.yml/g.exec(y)
}
