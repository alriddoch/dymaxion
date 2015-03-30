// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_SHADER_FACTORY_IMPL_H
#define DYMAXION_SHADER_FACTORY_IMPL_H

#include <dymaxion/ShaderFactory.h>

namespace dymaxion {

template <class T>
ShaderFactory<T>::ShaderFactory()
{
}

template <class T>
ShaderFactory<T>::~ShaderFactory()
{
}

template <class T>
Shader * ShaderFactory<T>::newShader(Shader::Parameters const & params) const
{
  return new T(params);
}

} // namespace dymaxion

#endif // DYMAXION_SHADER_FACTORY_IMPL_H
