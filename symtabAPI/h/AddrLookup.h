/*
 * Copyright (c) 1996-2007 Barton P. Miller
 *
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 *
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __AddrLookup_H__
#define __AddrLookup_H__

#include "Annotatable.h"

namespace Dyninst {
namespace SymtabAPI {

class AddressTranslate;
class LoadedLib;

//Needed for Linux and Solaris
class ProcessReader {
 public:
   PID pid;

   ProcessReader(PID pid_);
   ProcessReader();

   virtual bool start() = 0;
   virtual bool readAddressSpace(Address inTraced, unsigned amount, 
                                 void *inSelf) = 0;
   virtual bool done() = 0;
   virtual ~ProcessReader() {}
};

typedef struct {
   std::string name;
   Address codeAddr;
   Address dataAddr;
} LoadedLibrary;

class AddressLookup : public AnnotatableSparse
{
 private:
   AddressTranslate *translator;
   AddressLookup(AddressTranslate *trans);
   static dyn_hash_map<std::string, std::vector<Symbol *> > syms;
   int getSymsVector(std::string str);
   std::vector<Symbol *> *getSymsVector(LoadedLib *lib);


 public:
   SYMTAB_EXPORT static AddressLookup *createAddressLookup(ProcessReader *reader = NULL);
   SYMTAB_EXPORT static AddressLookup *createAddressLookup(PID pid, ProcessReader *reader = NULL);
   SYMTAB_EXPORT static AddressLookup *createAddressLookup(const std::vector<LoadedLibrary> &name_addrs);
   
   SYMTAB_EXPORT bool getAddress(Symtab *tab, Symbol *sym, Address &addr);
   SYMTAB_EXPORT bool getAddress(Symtab *tab, Offset off, Address &addr);

   SYMTAB_EXPORT bool getSymbol(Address addr, Symbol* &sym, Symtab* &tab, bool close = false);
   SYMTAB_EXPORT bool getOffset(Address addr, Symtab* &tab, Offset &off);
   
   SYMTAB_EXPORT bool getAllSymtabs(std::vector<Symtab *> &tabs);
   SYMTAB_EXPORT bool getLoadAddress(Symtab* sym, Address &load_addr);
   SYMTAB_EXPORT bool getDataLoadAddress(Symtab* sym, Address &load_addr);

   SYMTAB_EXPORT bool getLoadAddresses(std::vector<LoadedLibrary> &name_addrs);

   SYMTAB_EXPORT bool refresh();

   SYMTAB_EXPORT Address getLibraryTrapAddrSysV();

   
   SYMTAB_EXPORT virtual ~AddressLookup();
};

}
}

#endif
