#include <iostream>

int main() {
  int cases, lines, i, j;

  std::cin >> cases;

  for (i = 0; i < cases; i++) {
    std::cin >> lines;

    // Output the stanza number.
    std::cout << "Stanza #" << (i+1) << ":\n";

    for (j = 0; j < lines; j++) {
      std::cout << "This song's gonna get stuck inside yo'\n";
    }
    std::cout << "head\n";

    // Follow each case with a blank line.
    std::cout << std::endl;
  }

  return 0;
}
