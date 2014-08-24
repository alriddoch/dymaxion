// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#ifndef DYMAXION_BUFFER_H
#define DYMAXION_BUFFER_H

namespace dymaxion {

class Segment;

/// \brief Template for managing buffers of data for a segment.
template<typename DataType>
class Buffer {
  public:
    /// The terrain height segment this buffer is associated with.
    const Segment & m_segment;
  private:
    /// The number of data values per height point.
    const unsigned int m_channels;
    /// The size of segment, m_res + 1.
    const unsigned int m_size;
    /// Pointer to buffer containing data values.
    DataType * m_data = 0;

  public:
    /// \brief Constructor.
    ///
    /// @param segment terrain height segment this buffer is associated with.
    /// @param channels number of data values per height point.
    explicit Buffer(const Segment & segment, unsigned int channels = 4);
    virtual ~Buffer();

    /// \brief Retrieve the data value at a given point.
    ///
    /// Access the data value associated with given point in the segment
    /// in a given channel in this buffer.
    /// @return a reference to the value at the point requested.
    DataType & operator()(unsigned int x,unsigned int y,unsigned int channel) {
        return m_data[(y * m_size + x) * m_channels + channel];
    }

    /// \brief Retrieve the data value at a given point.
    ///
    /// Return the data value associated with given point in the segment
    /// in a given channel in this buffer.
    /// @return the value at the point requested.
    const DataType & operator()(unsigned int x,
                                unsigned int y,
                                unsigned int channel) const {
        return m_data[(y * m_size + x) * m_channels + channel];
    }
    
    /// Accessor for the terrain height segment this buffer is associated with.
    const Segment & getSegment() const {
        return m_segment;
    }

    /// Accessor for the size of segment, m_res + 1.
    unsigned int getSize() const {
        return m_size;
    }

    /// Accessor for the number of data values per height point.
    unsigned int getChannels() const {
        return m_channels;
    }

    /// Accessor for a pointer to buffer containing data values.
    DataType * getData() {
        return m_data;
    }

    /// \brief Allocate the storage required by the buffer.
    ///
    /// Allocate memory based on the size and number of channels required
    /// by the buffer.
    void allocate() {
        m_data = new DataType[m_size * m_size * m_channels];
    }

    /// \brief Determine if this buffer has valid allocated storage.
    ///
    /// @return true if storage is allocated.
    bool isValid() const {
        return (m_data != 0);
    }

    /// \brief De-allocate the storage for this buffer.
    ///
    /// Free the storage allocate for this buffer.
    void invalidate() {
        delete [] m_data;
        m_data = 0;
    }

};

} // namespace dymaxion

#endif // DYMAXION_BUFFER_H
