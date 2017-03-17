//
//  main.cpp
//  Biblioteka
//
//  Created by Kamil Kosiński on 21/01/2017.
//  Copyright © 2017 Kamil Kosiński. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

#include "file.h"
#include "book.h"
#include "library.h"

int main(){
    Library *lib = new Library();
    lib->menu();
    delete lib;
    return 0;
}
