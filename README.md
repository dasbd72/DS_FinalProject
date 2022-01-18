# DS FinalProject

## Compile

### Windows

`g++ -std=c++17 -o essay-search.exe ./*.cpp -lstdc++fs`

### Linux

`g++ -std=c++17 -o essay-search ./src/*.cpp -lstdc++fs`

## Execute

`./essay-search [data_folder_path] [query.txt] [output.txt]`

## Querry

- `Word` : prefix search
- `"Word"` : exact search
- `*Word*` : suffix search
- `\+` : and
- `/` : or

## Method

- Data Structure : trie
- Optimization
  - Parse query from right
  - build two tries

## Versions

- Beta 1 : 1/18 12:51
