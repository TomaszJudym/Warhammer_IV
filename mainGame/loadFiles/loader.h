//
// Created by Jebac Microsoft on 2/11/2018.
//
#include "../Game.h"

#ifndef _LOADER_H
#define _LOADER_H

#include <stdexcept>

template <typename Resource>
void loader( Resource* entity, const std::string& path )
{
    if( !entity->loadFromFile(path) )
    {
        throw std::runtime_error( "error: failed to load " + path );
    }
}

#endif // _LOADER_H
