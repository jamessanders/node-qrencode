#include <node/v8.h>
#include <node/node.h>
#include <qrencode.h>
#include <string.h>
#include <stdio.h>

using namespace v8;
using namespace node;

namespace qrencode_v8 {

  Handle<Value> EncodeString( const Arguments &args ) {

      HandleScope scope;
      
      Local<String> str   = args[0]->ToString();
      Local<Int32>  level = args[1]->ToInt32();
      Local<Int32>  hint  = args[2]->ToInt32();

      String::AsciiValue ascii(str);

      QRcode *qrc = QRcode_encodeString(*ascii, 0, (QRecLevel) level->Value(), (QRencodeMode) hint->Value(), 1);

      int len = qrc->width * qrc->width;

      Local<Array> outstr = Array::New(len);

      for (int i = 0; i < len; i++) {
        outstr->Set(Integer::New(i), Integer::New(int(qrc->data[i])));
      }

      Local <Object> outO = Object::New();
      outO->Set(String::NewSymbol("data"), outstr);
      outO->Set(String::NewSymbol("width"), Integer::New(qrc->width));
      outO->Set(String::NewSymbol("version"), Integer::New(qrc->version));
      return outO;

  }
}

extern "C" void init (Handle<Object> target) {

  NODE_DEFINE_CONSTANT(target, QR_MODE_AN);
  NODE_DEFINE_CONSTANT(target, QR_MODE_8);
  NODE_DEFINE_CONSTANT(target, QR_MODE_KANJI);

  NODE_DEFINE_CONSTANT(target, QR_ECLEVEL_L);
  NODE_DEFINE_CONSTANT(target, QR_ECLEVEL_M);
  NODE_DEFINE_CONSTANT(target, QR_ECLEVEL_Q);
  NODE_DEFINE_CONSTANT(target, QR_ECLEVEL_H);

  Local<FunctionTemplate> t = FunctionTemplate::New(qrencode_v8::EncodeString);

  target->Set( String::NewSymbol( "encodeString" ), t->GetFunction() );
}

