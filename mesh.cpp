#include "mesh.h"
#include <ctime>
#include <iostream>
using namespace std;
#define UNIT 10.0f

Mesh::Mesh()
{

}

bool Mesh::readPointers(string file_name)
{
    if (file_name.find(".hex") != file_name.size() - 4)
    {
        cout << "Error : not a .hex file!" << endl;
        return false;
    }
    std::ifstream fs(file_name.c_str());

    int lineCount;
    char   buffer[_INPUTLINESIZE_];
    char * buff;
    char * next_str;
    unsigned int nv, nt;
    lineCount = 0;
    nv = 0;		// num of vertices
    nt = 0;		// num of tet
    vector<GLfloat> tempV;
    vector<GLint> tempH;

    int idx[9];
    double start, end, tdiff;

    start = clock();
    while ((buff = read_line_chars(buffer, fs, lineCount)) != NULL)
    {
        //trim_str(buffer);
        if (buff[0] != '#')
        {
            if ((buffer[0] == 'v') || (buffer[0] == 'V'))
            {
                next_str = buff;
                for (unsigned int i = 0; i < 3; i++)
                {
                    next_str = find_next_sub_str(next_str);
                    //std::istringstream ss(std::string(next_str));
                    //ss >> v[i];
                    tempV.push_back(atof(next_str));
                }
                ++nv;


            }

            if ((buffer[0] == 'h') || (buffer[0] == 'H'))
            {
                next_str = buffer;
                for (unsigned int i = 0; i < 8; i++)
                {
                    next_str = find_next_sub_str(next_str);
                    //std::istringstream ss(std::string(next_str));
                    //ss >> idx[i];
                    idx[i] = atoi(next_str);
                    tempH.push_back(idx[i] - 1);
//					sequence[ns++] = idx[i] - 1;
                }
                ++nt;
                //break;
            }

        } // end of if '#'
    } // end of while
    fs.close();
    end = clock();

    vertices = new GLfloat[tempV.size()];
    sequence = new GLint[tempH.size()];
    for (int i = 0; i < tempV.size(); i++)
        vertices[i] = tempV[i] * UNIT;
    vector<GLfloat>(tempV).swap(tempV);		// clear tempV
    for (int i = 0; i < tempH.size(); i++)
        sequence[i] = tempH[i];
    vector<GLint>(tempH).swap(tempH);		// clear tempS

    v_cnt = nv;
    h_cnt = nt;
    tdiff = end - start;
    cout << "Time use: " << tdiff << endl;
    cout << "Total vertices: " << v_cnt << endl;
    cout << "Total tet: " << nt << endl;

    return true;
}

void Mesh::loadPointers(string file_name)
{
    readPointers(file_name);

    const int indexNum = h_cnt * 24;
    item_indices = new GLushort[indexNum];
    wire_indices = new GLushort[indexNum];
    cout << "indexNum: " << indexNum << endl;
    const int step1 = 24;
    const int step2 = 8;

    for (int cnt = 0; cnt < h_cnt; cnt++)
    {
        // item indices
        item_indices[cnt * step1 + 0] = sequence[0 + step2 * cnt];
        item_indices[cnt * step1 + 1] = sequence[1 + step2 * cnt];
        item_indices[cnt * step1 + 2] = sequence[2 + step2 * cnt];
        item_indices[cnt * step1 + 3] = sequence[3 + step2 * cnt];
        item_indices[cnt * step1 + 4] = sequence[0 + step2 * cnt];
        item_indices[cnt * step1 + 5] = sequence[1 + step2 * cnt];
        item_indices[cnt * step1 + 6] = sequence[5 + step2 * cnt];
        item_indices[cnt * step1 + 7] = sequence[4 + step2 * cnt];
        item_indices[cnt * step1 + 8] = sequence[5 + step2 * cnt];
        item_indices[cnt * step1 + 9] = sequence[4 + step2 * cnt];
        item_indices[cnt * step1 + 10] = sequence[7 + step2 * cnt];
        item_indices[cnt * step1 + 11] = sequence[6 + step2 * cnt];
        item_indices[cnt * step1 + 12] = sequence[2 + step2 * cnt];
        item_indices[cnt * step1 + 13] = sequence[3 + step2 * cnt];
        item_indices[cnt * step1 + 14] = sequence[7 + step2 * cnt];
        item_indices[cnt * step1 + 15] = sequence[6 + step2 * cnt];
        item_indices[cnt * step1 + 16] = sequence[1 + step2 * cnt];
        item_indices[cnt * step1 + 17] = sequence[2 + step2 * cnt];
        item_indices[cnt * step1 + 18] = sequence[6 + step2 * cnt];
        item_indices[cnt * step1 + 19] = sequence[5 + step2 * cnt];
        item_indices[cnt * step1 + 20] = sequence[0 + step2 * cnt];
        item_indices[cnt * step1 + 21] = sequence[3 + step2 * cnt];
        item_indices[cnt * step1 + 22] = sequence[7 + step2 * cnt];
        item_indices[cnt * step1 + 23] = sequence[4 + step2 * cnt];
        // wire indices
        wire_indices[cnt * step1 + 0] = sequence[0 + step2 * cnt];
        wire_indices[cnt * step1 + 1] = sequence[1 + step2 * cnt];
        wire_indices[cnt * step1 + 2] = sequence[1 + step2 * cnt];
        wire_indices[cnt * step1 + 3] = sequence[2 + step2 * cnt];
        wire_indices[cnt * step1 + 4] = sequence[2 + step2 * cnt];
        wire_indices[cnt * step1 + 5] = sequence[3 + step2 * cnt];
        wire_indices[cnt * step1 + 6] = sequence[3 + step2 * cnt];
        wire_indices[cnt * step1 + 7] = sequence[0 + step2 * cnt];
        wire_indices[cnt * step1 + 8] = sequence[0 + step2 * cnt];
        wire_indices[cnt * step1 + 9] = sequence[4 + step2 * cnt];
        wire_indices[cnt * step1 + 10] = sequence[4 + step2 * cnt];
        wire_indices[cnt * step1 + 11] = sequence[5 + step2 * cnt];
        wire_indices[cnt * step1 + 12] = sequence[5 + step2 * cnt];
        wire_indices[cnt * step1 + 13] = sequence[6 + step2 * cnt];
        wire_indices[cnt * step1 + 14] = sequence[6 + step2 * cnt];
        wire_indices[cnt * step1 + 15] = sequence[7 + step2 * cnt];
        wire_indices[cnt * step1 + 16] = sequence[7 + step2 * cnt];
        wire_indices[cnt * step1 + 17] = sequence[4 + step2 * cnt];
        wire_indices[cnt * step1 + 18] = sequence[3 + step2 * cnt];
        wire_indices[cnt * step1 + 19] = sequence[7 + step2 * cnt];
        wire_indices[cnt * step1 + 20] = sequence[2 + step2 * cnt];
        wire_indices[cnt * step1 + 21] = sequence[6 + step2 * cnt];
        wire_indices[cnt * step1 + 22] = sequence[1 + step2 * cnt];
        wire_indices[cnt * step1 + 23] = sequence[5 + step2 * cnt];
    }
}

void Mesh::draw()
{
}
