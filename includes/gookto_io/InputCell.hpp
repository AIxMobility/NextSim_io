#ifndef INPUTCELL_H
#define INPUTCELL_H

#include "BaseClass.hpp"


class InputCell: public MetaData
{
    private:
        //Data Members for the cell
        double offset;
    public:
        // Constructor and destructor for the cell
        InputCell(std::size_t id_val, double offset_val, double length_val) : MetaData(id_val, length_val)
        {
            offset = offset_val;
        }

        ~InputCell() = default;
        InputCell(const InputCell& cell) = default;
        InputCell& operator=(const InputCell& cell) = default;


        void setOffset(double offset_val){offset = offset_val;}
        double getOffset(){return offset;}
};

#endif