#ifndef __INCLUDED_LINERENDERMODEL_H
#define __INCLUDED_LINERENDERMODEL_H

#include "../rendermodel/rendermodel.h"

class LineRenderModel : public RenderModel
{
    public:
        LineRenderModel();
        ~LineRenderModel();

        void render();
};

#endif