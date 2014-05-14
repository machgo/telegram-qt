/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "CRawStream.hpp"

#include <QIODevice>

template CRawStream &CRawStream::operator>>(TLNumber128 &v);
template CRawStream &CRawStream::operator>>(TLNumber256 &v);

template CRawStream &CRawStream::operator<<(const TLNumber128 &v);
template CRawStream &CRawStream::operator<<(const TLNumber256 &v);

CRawStream::CRawStream(QIODevice *d) :
    m_device(d)
{

}

void CRawStream::setDevice(QIODevice *newDevice)
{
    m_device = newDevice;
}

void CRawStream::unsetDevice()
{
    m_device = 0;
}

bool CRawStream::atEnd() const
{
    return m_device ? m_device->atEnd() : true;
}

int CRawStream::bytesRemaining() const
{
    return m_device->bytesAvailable();
}

QByteArray CRawStream::readBytes(int count)
{
    return m_device->read(count);
}

CRawStream &CRawStream::operator>>(qint32 &i)
{
    m_device->read((char *)&i, 4);

    return *this;
}

CRawStream &CRawStream::operator>>(qint64 &i)
{
    m_device->read((char *)&i, 8);

    return *this;
}

CRawStream &CRawStream::operator<<(qint32 i)
{
    m_device->write((const char *) &i, 4);

    return *this;
}

CRawStream &CRawStream::operator<<(qint64 i)
{
    m_device->write((const char *) &i, 8);

    return *this;
}
