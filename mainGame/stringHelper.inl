template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

std::string cutTo30charLines( char* _input )
{
    std::string toRet = "";
    size_t i = 0;
    while( *(_input+i) != '\0' )
    {
        if( i%30 == 0 )
        {
            toRet += '\n';
        }
        toRet += *(_input+i);
        ++i;
    }
    return toRet;
}
