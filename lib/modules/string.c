#include "string.h"

_String String = {
    .length = length
};

/**
* @method length
* @param character
*/
uint16 length(string character)
{
    uint16 i = 1;
    while(character[i++]);  
    return --i;
}
