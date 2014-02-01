// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include <generated/Account-odb.hxx>
#include "generated/Split-odb.hxx"
#include "generated/Transaction-odb.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/sqlite/traits.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/sqlite/transaction.hxx>
#include <odb/sqlite/connection.hxx>
#include <odb/sqlite/statement.hxx>
#include <odb/sqlite/statement-cache.hxx>
#include <odb/sqlite/simple-object-statements.hxx>
#include <odb/sqlite/container-statements.hxx>
#include <odb/sqlite/exceptions.hxx>
#include <odb/sqlite/simple-object-result.hxx>

namespace odb
{
  // Account
  //

  const char alias_traits<  ::opencash::model::Account,
    id_sqlite,
    access::object_traits_impl< ::opencash::model::Account, id_sqlite >::parent_tag>::
  table_name[] = "\"parent\"";

  struct access::object_traits_impl< ::opencash::model::Account, id_sqlite >::extra_statement_cache_type
  {
    sqlite::container_statements_impl< children_traits > _children;
    sqlite::container_statements_impl< splits_traits > _splits;

    extra_statement_cache_type (
      sqlite::connection& c,
      image_type&,
      sqlite::binding& id,
      sqlite::binding&)
    : _children (c, id),
      _splits (c, id)
    {
    }
  };

  // _children
  //

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::children_traits::
  select_statement[] =
  "SELECT "
  "\"accounts\".\"uuid\" "
  "FROM \"accounts\" "
  "WHERE \"accounts\".\"parent\"=?";

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::children_traits::
  insert_statement[] =
  "";

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::children_traits::
  delete_statement[] =
  "";

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::children_traits::
  bind (sqlite::bind* b,
        const sqlite::bind* id,
        std::size_t id_size,
        data_image_type& d)
  {
    using namespace sqlite;

    statement_kind sk (statement_select);
    ODB_POTENTIALLY_UNUSED (sk);

    size_t n (0);

    // object_id
    //
    if (id != 0)
      std::memcpy (&b[n], id, id_size * sizeof (id[0]));
    n += id_size;

    // value
    //
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = d.value_value.data ();
    b[n].size = &d.value_size;
    b[n].capacity = d.value_value.capacity ();
    b[n].is_null = &d.value_null;
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::children_traits::
  grow (data_image_type& i,
        bool* t)
  {
    bool grew (false);

    // value
    //
    if (t[0UL])
    {
      i.value_value.capacity (i.value_size);
      grew = true;
    }

    if (grew)
      i.version++;
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::children_traits::
  init (value_type& v,
        const data_image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (db);

    // value
    //
    {
      typedef object_traits< ::opencash::model::Account > obj_traits;
      typedef odb::pointer_traits< value_type > ptr_traits;

      if (i.value_null)
        v = ptr_traits::pointer_type ();
      else
      {
        obj_traits::id_type id;
        sqlite::value_traits<
            obj_traits::id_type,
            sqlite::id_text >::set_value (
          id,
          i.value_value,
          i.value_size,
          i.value_null);

        // If a compiler error points to the line below, then
        // it most likely means that a pointer used in a member
        // cannot be initialized from an object pointer.
        //
        v = ptr_traits::pointer_type (
          static_cast<sqlite::database*> (db)->load<
            obj_traits::object_type > (id));

        if (odb::pointer_traits<ptr_traits::strong_pointer_type>::null_ptr (
              ptr_traits::lock (v)))
          throw session_required ();
      }
    }
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::children_traits::
  insert (index_type, const value_type&, void*)
  {
  }

  bool access::object_traits_impl< ::opencash::model::Account, id_sqlite >::children_traits::
  select (index_type&, value_type& v, void* d)
  {
    using namespace sqlite;
    using sqlite::select_statement;

    statements_type& sts (*static_cast< statements_type* > (d));
    data_image_type& di (sts.data_image ());

    init (v, di, &sts.connection ().database ());

    if (sts.data_binding_test_version ())
    {
      const binding& id (sts.id_binding ());
      bind (sts.data_bind (), id.bind, id.count, di);
      sts.data_binding_update_version ();
    }

    select_statement& st (sts.select_statement ());
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      grow (di, sts.select_image_truncated ());

      if (sts.data_binding_test_version ())
      {
        bind (sts.data_bind (), 0, sts.id_binding ().count, di);
        sts.data_binding_update_version ();
        st.refetch ();
      }
    }

    return r != select_statement::no_data;
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::children_traits::
  delete_ (void*)
  {
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::children_traits::
  load (container_type& c,
        statements_type& sts)
  {
    using namespace sqlite;
    using sqlite::select_statement;

    const binding& id (sts.id_binding ());

    if (sts.data_binding_test_version ())
    {
      bind (sts.data_bind (), id.bind, id.count, sts.data_image ());
      sts.data_binding_update_version ();
    }

    select_statement& st (sts.select_statement ());
    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      data_image_type& di (sts.data_image ());
      grow (di, sts.select_image_truncated ());

      if (sts.data_binding_test_version ())
      {
        bind (sts.data_bind (), 0, id.count, di);
        sts.data_binding_update_version ();
        st.refetch ();
      }
    }

    bool more (r != select_statement::no_data);

    functions_type& fs (sts.functions ());
    fs.ordered_ = false;
    container_traits_type::load (c, more, fs);
  }

  // _splits
  //

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::splits_traits::
  select_statement[] =
  "SELECT "
  "\"splits\".\"uuid\" "
  "FROM \"splits\" "
  "WHERE \"splits\".\"account\"=?";

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::splits_traits::
  insert_statement[] =
  "";

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::splits_traits::
  delete_statement[] =
  "";

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::splits_traits::
  bind (sqlite::bind* b,
        const sqlite::bind* id,
        std::size_t id_size,
        data_image_type& d)
  {
    using namespace sqlite;

    statement_kind sk (statement_select);
    ODB_POTENTIALLY_UNUSED (sk);

    size_t n (0);

    // object_id
    //
    if (id != 0)
      std::memcpy (&b[n], id, id_size * sizeof (id[0]));
    n += id_size;

    // value
    //
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = d.value_value.data ();
    b[n].size = &d.value_size;
    b[n].capacity = d.value_value.capacity ();
    b[n].is_null = &d.value_null;
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::splits_traits::
  grow (data_image_type& i,
        bool* t)
  {
    bool grew (false);

    // value
    //
    if (t[0UL])
    {
      i.value_value.capacity (i.value_size);
      grew = true;
    }

    if (grew)
      i.version++;
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::splits_traits::
  init (value_type& v,
        const data_image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (db);

    // value
    //
    {
      typedef object_traits< ::opencash::model::Split > obj_traits;
      typedef odb::pointer_traits< value_type > ptr_traits;

      if (i.value_null)
        v = ptr_traits::pointer_type ();
      else
      {
        obj_traits::id_type id;
        sqlite::value_traits<
            obj_traits::id_type,
            sqlite::id_text >::set_value (
          id,
          i.value_value,
          i.value_size,
          i.value_null);

        // If a compiler error points to the line below, then
        // it most likely means that a pointer used in a member
        // cannot be initialized from an object pointer.
        //
        v = ptr_traits::pointer_type (
          static_cast<sqlite::database*> (db)->load<
            obj_traits::object_type > (id));
      }
    }
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::splits_traits::
  insert (index_type, const value_type&, void*)
  {
  }

  bool access::object_traits_impl< ::opencash::model::Account, id_sqlite >::splits_traits::
  select (index_type&, value_type& v, void* d)
  {
    using namespace sqlite;
    using sqlite::select_statement;

    statements_type& sts (*static_cast< statements_type* > (d));
    data_image_type& di (sts.data_image ());

    init (v, di, &sts.connection ().database ());

    if (sts.data_binding_test_version ())
    {
      const binding& id (sts.id_binding ());
      bind (sts.data_bind (), id.bind, id.count, di);
      sts.data_binding_update_version ();
    }

    select_statement& st (sts.select_statement ());
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      grow (di, sts.select_image_truncated ());

      if (sts.data_binding_test_version ())
      {
        bind (sts.data_bind (), 0, sts.id_binding ().count, di);
        sts.data_binding_update_version ();
        st.refetch ();
      }
    }

    return r != select_statement::no_data;
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::splits_traits::
  delete_ (void*)
  {
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::splits_traits::
  load (container_type& c,
        statements_type& sts)
  {
    using namespace sqlite;
    using sqlite::select_statement;

    const binding& id (sts.id_binding ());

    if (sts.data_binding_test_version ())
    {
      bind (sts.data_bind (), id.bind, id.count, sts.data_image ());
      sts.data_binding_update_version ();
    }

    select_statement& st (sts.select_statement ());
    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      data_image_type& di (sts.data_image ());
      grow (di, sts.select_image_truncated ());

      if (sts.data_binding_test_version ())
      {
        bind (sts.data_bind (), 0, id.count, di);
        sts.data_binding_update_version ();
        st.refetch ();
      }
    }

    bool more (r != select_statement::no_data);

    functions_type& fs (sts.functions ());
    fs.ordered_ = false;
    container_traits_type::load (c, more, fs);
  }

  access::object_traits_impl< ::opencash::model::Account, id_sqlite >::id_type
  access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  id (const image_type& i)
  {
    sqlite::database* db (0);
    ODB_POTENTIALLY_UNUSED (db);

    id_type id;
    {
      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_value (
        id,
        i._uuid_value,
        i._uuid_size,
        i._uuid_null);
    }

    return id;
  }

  bool access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  grow (image_type& i,
        bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // _uuid
    //
    if (t[0UL])
    {
      i._uuid_value.capacity (i._uuid_size);
      grew = true;
    }

    // _name
    //
    if (t[1UL])
    {
      i._name_value.capacity (i._name_size);
      grew = true;
    }

    // _descr
    //
    if (t[2UL])
    {
      i._descr_value.capacity (i._descr_size);
      grew = true;
    }

    // _type
    //
    t[3UL] = false;

    // _parent
    //
    if (t[4UL])
    {
      i._parent_value.capacity (i._parent_size);
      grew = true;
    }

    return grew;
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  bind (sqlite::bind* b,
        image_type& i,
        sqlite::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace sqlite;

    std::size_t n (0);

    // _uuid
    //
    if (sk != statement_update)
    {
      b[n].type = sqlite::image_traits<
        ::std::string,
        sqlite::id_text>::bind_value;
      b[n].buffer = i._uuid_value.data ();
      b[n].size = &i._uuid_size;
      b[n].capacity = i._uuid_value.capacity ();
      b[n].is_null = &i._uuid_null;
      n++;
    }

    // _name
    //
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = i._name_value.data ();
    b[n].size = &i._name_size;
    b[n].capacity = i._name_value.capacity ();
    b[n].is_null = &i._name_null;
    n++;

    // _descr
    //
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = i._descr_value.data ();
    b[n].size = &i._descr_size;
    b[n].capacity = i._descr_value.capacity ();
    b[n].is_null = &i._descr_null;
    n++;

    // _type
    //
    b[n].type = sqlite::bind::integer;
    b[n].buffer = &i._type_value;
    b[n].is_null = &i._type_null;
    n++;

    // _parent
    //
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = i._parent_value.data ();
    b[n].size = &i._parent_size;
    b[n].capacity = i._parent_value.capacity ();
    b[n].is_null = &i._parent_null;
    n++;
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  bind (sqlite::bind* b, id_image_type& i)
  {
    std::size_t n (0);
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = i.id_value.data ();
    b[n].size = &i.id_size;
    b[n].capacity = i.id_value.capacity ();
    b[n].is_null = &i.id_null;
  }

  bool access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  init (image_type& i,
        const object_type& o,
        sqlite::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace sqlite;

    bool grew (false);

    // _uuid
    //
    if (sk == statement_insert)
    {
      ::std::string const& v =
        o._uuid;

      bool is_null (false);
      std::size_t cap (i._uuid_value.capacity ());
      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_image (
        i._uuid_value,
        i._uuid_size,
        is_null,
        v);
      i._uuid_null = is_null;
      grew = grew || (cap != i._uuid_value.capacity ());
    }

    // _name
    //
    {
      ::std::string const& v =
        o._name;

      bool is_null (false);
      std::size_t cap (i._name_value.capacity ());
      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_image (
        i._name_value,
        i._name_size,
        is_null,
        v);
      i._name_null = is_null;
      grew = grew || (cap != i._name_value.capacity ());
    }

    // _descr
    //
    {
      ::std::string const& v =
        o._descr;

      bool is_null (false);
      std::size_t cap (i._descr_value.capacity ());
      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_image (
        i._descr_value,
        i._descr_size,
        is_null,
        v);
      i._descr_null = is_null;
      grew = grew || (cap != i._descr_value.capacity ());
    }

    // _type
    //
    {
      ::opencash::model::Account::AccountType const& v =
        o._type;

      bool is_null (false);
      sqlite::value_traits<
          ::opencash::model::Account::AccountType,
          sqlite::id_integer >::set_image (
        i._type_value,
        is_null,
        v);
      i._type_null = is_null;
    }

    // _parent
    //
    {
      ::opencash::model::Account::AccountPtr const& v =
        o._parent;

      typedef object_traits< ::opencash::model::Account > obj_traits;
      typedef odb::pointer_traits< ::opencash::model::Account::AccountPtr > ptr_traits;

      bool is_null (ptr_traits::null_ptr (v));
      if (!is_null)
      {
        const obj_traits::id_type& id (
          obj_traits::id (ptr_traits::get_ref (v)));

        std::size_t cap (i._parent_value.capacity ());
        sqlite::value_traits<
            obj_traits::id_type,
            sqlite::id_text >::set_image (
          i._parent_value,
          i._parent_size,
          is_null,
          id);
        i._parent_null = is_null;
        grew = grew || (cap != i._parent_value.capacity ());
      }
      else
        i._parent_null = true;
    }

    return grew;
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  init (object_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // _uuid
    //
    {
      ::std::string& v =
        o._uuid;

      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_value (
        v,
        i._uuid_value,
        i._uuid_size,
        i._uuid_null);
    }

    // _name
    //
    {
      // From Account.h:71:18
      ::std::string v;

      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_value (
        v,
        i._name_value,
        i._name_size,
        i._name_null);

      // From Account.h:71:18
      o.setName (v);
    }

    // _descr
    //
    {
      // From Account.h:74:18
      ::std::string v;

      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_value (
        v,
        i._descr_value,
        i._descr_size,
        i._descr_null);

      // From Account.h:74:18
      o.setDescr (v);
    }

    // _type
    //
    {
      // From Account.h:77:18
      ::opencash::model::Account::AccountType v;

      sqlite::value_traits<
          ::opencash::model::Account::AccountType,
          sqlite::id_integer >::set_value (
        v,
        i._type_value,
        i._type_null);

      // From Account.h:77:18
      o.setType (v);
    }

    // _parent
    //
    {
      // From Account.h:80:18
      ::opencash::model::Account::AccountPtr v;

      typedef object_traits< ::opencash::model::Account > obj_traits;
      typedef odb::pointer_traits< ::opencash::model::Account::AccountPtr > ptr_traits;

      if (i._parent_null)
        v = ptr_traits::pointer_type ();
      else
      {
        obj_traits::id_type id;
        sqlite::value_traits<
            obj_traits::id_type,
            sqlite::id_text >::set_value (
          id,
          i._parent_value,
          i._parent_size,
          i._parent_null);

        // If a compiler error points to the line below, then
        // it most likely means that a pointer used in a member
        // cannot be initialized from an object pointer.
        //
        v = ptr_traits::pointer_type (
          static_cast<sqlite::database*> (db)->load<
            obj_traits::object_type > (id));
      }

      // From Account.h:80:18
      o.setParent (v);
    }
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  init (id_image_type& i, const id_type& id)
  {
    bool grew (false);
    {
      bool is_null (false);
      std::size_t cap (i.id_value.capacity ());
      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_image (
        i.id_value,
        i.id_size,
        is_null,
        id);
      i.id_null = is_null;
      grew = grew || (cap != i.id_value.capacity ());
    }

    if (grew)
      i.version++;
  }

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::persist_statement[] =
  "INSERT INTO \"accounts\" "
  "(\"uuid\", "
  "\"name\", "
  "\"descr\", "
  "\"type\", "
  "\"parent\") "
  "VALUES "
  "(?, ?, ?, ?, ?)";

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::find_statement[] =
  "SELECT "
  "\"accounts\".\"uuid\", "
  "\"accounts\".\"name\", "
  "\"accounts\".\"descr\", "
  "\"accounts\".\"type\", "
  "\"accounts\".\"parent\" "
  "FROM \"accounts\" "
  "WHERE \"accounts\".\"uuid\"=?";

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::update_statement[] =
  "UPDATE \"accounts\" "
  "SET "
  "\"name\"=?, "
  "\"descr\"=?, "
  "\"type\"=?, "
  "\"parent\"=? "
  "WHERE \"uuid\"=?";

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::erase_statement[] =
  "DELETE FROM \"accounts\" "
  "WHERE \"uuid\"=?";

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::query_statement[] =
  "SELECT\n"
  "\"accounts\".\"uuid\",\n"
  "\"accounts\".\"name\",\n"
  "\"accounts\".\"descr\",\n"
  "\"accounts\".\"type\",\n"
  "\"accounts\".\"parent\"\n"
  "FROM \"accounts\"\n"
  "LEFT JOIN \"accounts\" AS \"parent\" ON \"parent\".\"uuid\"=\"accounts\".\"parent\"";

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::erase_query_statement[] =
  "DELETE FROM \"accounts\"";

  const char access::object_traits_impl< ::opencash::model::Account, id_sqlite >::table_name[] =
  "\"accounts\"";

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  persist (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace sqlite;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    callback (db,
              obj,
              callback_event::pre_persist);

    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    if (im.version != sts.insert_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_insert);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    callback (db,
              obj,
              callback_event::post_persist);
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  update (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace sqlite;
    using sqlite::update_statement;

    callback (db, obj, callback_event::pre_update);

    sqlite::transaction& tr (sqlite::transaction::current ());
    sqlite::connection& conn (tr.connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    const id_type& id (
      obj._uuid);
    id_image_type& idi (sts.id_image ());
    init (idi, id);

    image_type& im (sts.image ());
    if (init (im, obj, statement_update))
      im.version++;

    bool u (false);
    binding& imb (sts.update_image_binding ());
    if (im.version != sts.update_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_update);
      sts.update_image_version (im.version);
      imb.version++;
      u = true;
    }

    binding& idb (sts.id_image_binding ());
    if (idi.version != sts.update_id_image_version () ||
        idb.version == 0)
    {
      if (idi.version != sts.id_image_version () ||
          idb.version == 0)
      {
        bind (idb.bind, idi);
        sts.id_image_version (idi.version);
        idb.version++;
      }

      sts.update_id_image_version (idi.version);

      if (!u)
        imb.version++;
    }

    update_statement& st (sts.update_statement ());
    if (st.execute () == 0)
      throw object_not_persistent ();

    callback (db, obj, callback_event::post_update);
    pointer_cache_traits::update (db, obj);
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  erase (database& db, const id_type& id)
  {
    using namespace sqlite;

    ODB_POTENTIALLY_UNUSED (db);

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& i (sts.id_image ());
    init (i, id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    if (sts.erase_statement ().execute () != 1)
      throw object_not_persistent ();

    pointer_cache_traits::erase (db, id);
  }

  access::object_traits_impl< ::opencash::model::Account, id_sqlite >::pointer_type
  access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  find (database& db, const id_type& id)
  {
    using namespace sqlite;

    {
      pointer_type p (pointer_cache_traits::find (db, id));

      if (!pointer_traits::null_ptr (p))
        return p;
    }

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (l.locked ())
    {
      if (!find_ (sts, &id))
        return pointer_type ();
    }

    pointer_type p (
      access::object_factory<object_type, pointer_type>::create ());
    pointer_traits::guard pg (p);

    pointer_cache_traits::insert_guard ig (
      pointer_cache_traits::insert (db, id, p));

    object_type& obj (pointer_traits::get_ref (p));

    if (l.locked ())
    {
      select_statement& st (sts.find_statement ());
      ODB_POTENTIALLY_UNUSED (st);

      callback (db, obj, callback_event::pre_load);
      init (obj, sts.image (), &db);
      load_ (sts, obj, false);
      sts.load_delayed (0);
      l.unlock ();
      callback (db, obj, callback_event::post_load);
      pointer_cache_traits::load (ig.position ());
    }
    else
      sts.delay_load (id, obj, ig.position ());

    ig.release ();
    pg.release ();
    return p;
  }

  bool access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  find (database& db, const id_type& id, object_type& obj)
  {
    using namespace sqlite;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    reference_cache_traits::position_type pos (
      reference_cache_traits::insert (db, id, obj));
    reference_cache_traits::insert_guard ig (pos);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, false);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    reference_cache_traits::load (pos);
    ig.release ();
    return true;
  }

  bool access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  reload (database& db, object_type& obj)
  {
    using namespace sqlite;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    const id_type& id  (
      obj._uuid);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, true);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    return true;
  }

  bool access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  find_ (statements_type& sts,
         const id_type* id)
  {
    using namespace sqlite;

    id_image_type& i (sts.id_image ());
    init (i, *id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    select_statement& st (sts.find_statement ());

    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      if (grow (im, sts.select_image_truncated ()))
        im.version++;

      if (im.version != sts.select_image_version ())
      {
        bind (imb.bind, im, statement_select);
        sts.select_image_version (im.version);
        imb.version++;
        st.refetch ();
      }
    }

    return r != select_statement::no_data;
  }

  void access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  load_ (statements_type& sts,
         object_type& obj,
         bool reload)
  {
    ODB_POTENTIALLY_UNUSED (reload);

    extra_statement_cache_type& esc (sts.extra_statement_cache ());

    // _children
    //
    {
      ::opencash::model::Account::WeakAccounts& v =
        obj._children;

      children_traits::load (
        v,
        esc._children);
    }

    // _splits
    //
    {
      ::std::vector< ::std::shared_ptr< ::opencash::model::Split > >& v =
        obj._splits;

      splits_traits::load (
        v,
        esc._splits);
    }
  }

  result< access::object_traits_impl< ::opencash::model::Account, id_sqlite >::object_type >
  access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  query (database&, const query_base_type& q)
  {
    using namespace sqlite;
    using odb::details::shared;
    using odb::details::shared_ptr;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    std::string text (query_statement);
    if (!q.empty ())
    {
      text += "\n";
      text += q.clause ();
    }

    q.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        conn,
        text,
        true,
        true,
        q.parameters_binding (),
        imb));

    st->execute ();

    shared_ptr< odb::object_result_impl<object_type> > r (
      new (shared) sqlite::object_result_impl<object_type> (
        q, st, sts, 0));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::opencash::model::Account, id_sqlite >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace sqlite;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());

    std::string text (erase_query_statement);
    if (!q.empty ())
    {
      text += ' ';
      text += q.clause ();
    }

    q.init_parameters ();
    delete_statement st (
      conn,
      text,
      q.parameters_binding ());

    return st.execute ();
  }
}

namespace odb
{
  static bool
  create_schema (database& db, unsigned short pass, bool drop)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (pass);
    ODB_POTENTIALLY_UNUSED (drop);

    if (drop)
    {
      switch (pass)
      {
        case 1:
        {
          return true;
        }
        case 2:
        {
          db.execute ("DROP TABLE IF EXISTS \"accounts\"");
          return false;
        }
      }
    }
    else
    {
      switch (pass)
      {
        case 1:
        {
          db.execute ("CREATE TABLE \"accounts\" (\n"
                      "  \"uuid\" TEXT NOT NULL PRIMARY KEY,\n"
                      "  \"name\" TEXT NOT NULL,\n"
                      "  \"descr\" TEXT NOT NULL,\n"
                      "  \"type\" INTEGER NOT NULL,\n"
                      "  \"parent\" TEXT NULL,\n"
                      "  CONSTRAINT \"parent_fk\"\n"
                      "    FOREIGN KEY (\"parent\")\n"
                      "    REFERENCES \"accounts\" (\"uuid\")\n"
                      "    DEFERRABLE INITIALLY DEFERRED)");
          return false;
        }
      }
    }

    return false;
  }

  static const schema_catalog_create_entry
  create_schema_entry_ (
    id_sqlite,
    "",
    &create_schema);
}

#include <odb/post.hxx>
