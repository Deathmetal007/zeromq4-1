/*
    Copyright (c) 2007-2009 FastMQ Inc.

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZMQ_IO_OBJECT_HPP_INCLUDED__
#define __ZMQ_IO_OBJECT_HPP_INCLUDED__

#include "object.hpp"

namespace zmq
{

    class io_object_t : public object_t
    {
    public:

        //  I/O object will live in the thread inherited from the parent.
        //  However, it's lifetime is managed by the owner.
        io_object_t (object_t *parent_, object_t *owner_);

    protected:

        //  Ask owner socket to terminate this I/O object. This may not happen
        void term ();

        //  I/O object destroys itself. No point in allowing others to invoke
        //  the destructor. At the same time, it has to be virtual so that
        //  generic io_object deallocation mechanism destroys specific type
        //  of I/O object correctly.
        virtual ~io_object_t ();

    private:

        //  Handlers for incoming commands.
        void process_term ();

        //  Socket owning this I/O object. It is responsible for destroying
        //  it when it's being closed.
        object_t *owner;

        io_object_t (const io_object_t&);
        void operator = (const io_object_t&);
    };

}

#endif
