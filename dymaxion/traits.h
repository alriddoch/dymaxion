// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2005 Alistair Riddoch

#ifndef DYMAXION_TRAITS_H
#define DYMAXION_TRAITS_H

namespace dymaxion
{

namespace traits
{

template <class AxixBox, int idx>
class axisbox_access;

template <class AxisBox>
class axisbox_construct;

template <class Point, int idx>
class point_access;

template <class Point>
class point_construct;

}

}

#endif // DYMAXION_TRAITS_H
