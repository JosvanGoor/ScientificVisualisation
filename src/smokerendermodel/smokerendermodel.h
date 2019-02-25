#ifndef __INCLUDED_SMOKERENDERMODEL_H
#define __INCLUDED_SMOKERENDERMODEL_H

#include "../rendermodel/rendermodel.h"

class SmokeRenderModel : public RenderModel
{
    public:
        SmokeRenderModel();
        ~SmokeRenderModel();

        void render();
};

#endif