# Dictionary and Auto-Suggest

A command-line C++ practice project for learning how tries support dictionary lookups and autocomplete. The program loads words and definitions from `dictionary.txt`.

## Features

- Browse dictionary entries and look up definitions.
- Enter a prefix such as `sma` to find matching words like `smart`.
- Add new entries for the current session.

## Run Locally

On Windows, compile `main.cpp` with a C++ compiler such as MinGW and run the program from the folder containing `dictionary.txt`. Use lowercase letters for lookups and prefixes.

The trie supports letters `a`–`z`. Some bundled entries contain spaces or hyphens, so remove those entries before running the current version.
