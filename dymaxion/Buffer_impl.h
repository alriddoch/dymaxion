// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#include <dymaxion/Buffer.h>

#include <dymaxion/Segment.h>

namespace dymaxion {

template <typename DataType>
Buffer<DataType>::Buffer(const Segment & segment, unsigned int channels) :
  m_segment(segment), m_channels(channels), m_size(segment.getSize())
{
}

template <typename DataType>
Buffer<DataType>::~Buffer()
{
  if (m_data != 0) {
    delete[] m_data;
  }
}

} // namespace dymaxion
