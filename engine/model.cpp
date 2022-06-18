#include "model.hpp"

model model::merge(const std::vector<model>& models, const bool single)
{
    model merged;

    unsigned int size   = 0;
    unsigned int offset = 0;

    for (const auto& model : models)
    {
        merged.vertices.insert(merged.vertices.end(), model.vertices.begin(),
                                                      model.vertices.end());
        for (const unsigned int index : model.indices)
        {
            merged.indices.push_back(index + size);
        }

        size += static_cast<unsigned int>(model.vertices.size());

        if (!single)
        {
            merged.submeshes.push_back({ static_cast<unsigned int>(offset * sizeof(unsigned int)),
                                         static_cast<int>(model.indices.size()) });
            offset += static_cast<unsigned int>(model.indices.size());
        }
    }

    if (single)
    {
        merged.submeshes.push_back({ 0, static_cast<int>(merged.indices.size()) });
    }

    return merged;
}
