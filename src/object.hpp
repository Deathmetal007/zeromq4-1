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

#ifndef __ZMQ_OBJECT_HPP_INCLUDED__
#define __ZMQ_OBJECT_HPP_INCLUDED__

#include "stdint.hpp"

namespace zmq
{

    //  Base class for all objects that participate in inter-thread
    //  communication.

    class object_t
    {
    public:

        object_t (class dispatcher_t *dispatcher_, int thread_slot_);
        object_t (object_t *parent_);
        ~object_t ();

        int get_thread_slot ();
        void process_command (struct command_t &cmd_);

    protected:

        //  Derived object can use following functions to interact with
        //  global repositories. See dispatcher.hpp for function details.
        int thread_slot_count ();
        class io_thread_t *choose_io_thread (uint64_t taskset_);

        //  Derived object can use these functions to send commands
        //  to other objects.
        void send_stop ();
        void send_plug (object_t *destination_);
        void send_own (object_t *destination_, object_t *object_);
        void send_bind (object_t *destination_);
        void send_term_req (object_t *destination_, object_t *object_);
        void send_term (object_t *destination_);
        void send_term_ack (object_t *destination_);

        //  These handlers can be overloaded by the derived objects. They are
        //  called when command arrives from another thread.
        virtual void process_stop ();
        virtual void process_plug ();
        virtual void process_own (object_t *object_);
        virtual void process_bind ();
        virtual void process_term_req (object_t *object_);
        virtual void process_term ();
        virtual void process_term_ack ();

        //  Pointer to the root of the infrastructure.
        class dispatcher_t *dispatcher;

        //  Slot ID of the thread the object belongs to.
        int thread_slot;

    private:

        void send_command (command_t &cmd_);

        object_t (const object_t&);
        void operator = (const object_t&);
    };

}

#endif
