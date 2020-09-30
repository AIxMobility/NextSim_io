#ifndef INPUTCELL_H
#define INPUTCELL_H

#include "BaseClass.hpp"

typedef unsigned long long u_ll;


class InputCell: public MetadataBase
{
    private:
        //Data Members for the cell
        float offset;
    public:
        // Constructor and destructor for the cell
        InputCell(u_ll id_val, float offset_val, float length_val) : MetadataBase(id_val, length_val)
        {
            offset = offset_val;
        }

        InputCell() : MetadataBase(){}
        ~InputCell() = default;
        InputCell(const InputCell& cell) = default;
        InputCell& operator=(const InputCell& cell) = default;


        void setOffset(float offset_val){offset = offset_val;}
        float getOffset(){return offset;}
};

#endif