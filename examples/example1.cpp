#include "../BNM-IL2CPP/BNM.hpp"
#include <cstdint>
#include <string>

// This examples work in Pixel Gun 3D v24.6.0

int main()
{

    // dont forgot about initialize
    IL2CPP::Initialize();
    /*
    Getting assemblies and images of assemblies
    */

    IL2CPP::Assembly *__AssemblyCSharp = IL2CPP::Domain()->Assembly("Assembly-CSharp");
    IL2CPP::Image *AssemblyCSharp = __AssemblyCSharp->Image();

    IL2CPP::Assembly *__mscorlib = IL2CPP::Domain()->Assembly("mscorlib");
    IL2CPP::Image *mscorlib = __mscorlib->Image();

    /*
    Getting classes
    */

    IL2CPP::Class *Klass_1 = AssemblyCSharp->Class("东丞丝丞万丒丛丂丐");
    IL2CPP::Class *Vector3_Klass = mscorlib->Class("UnityEngine.Vector3"); // namespace + name

    const char *Vector3_Klass_name = Vector3_Klass->Name(); // Vector3

    /*
    Creating instaces of classes
    */

    IL2CPP::Object *Vector3_Instance = IL2CPP::Object::New(Vector3_Klass);

    /*
    Getting and reading fields
    at the moment i didn't make settings fields but it ezzzz and i'll make it a little later
    */

    // Getting non-static field
    IL2CPP::Field *Vector3_X = Vector3_Instance->Field("x");

    // if field non-static, we need to pass instance to parameters
    int Vector3_X_Value = Vector3_X.GetValue<int>(Vector3_Instance); // 0 by default.

    // Getting static field
    IL2CPP::Field *Static_Field = Klass_1->Field("七丞丌丗专丕丕业下");
    int Static_Field_Value = Static_Field->GetValue<int>(); // 150
    /*
    if field is class instance just cast it to void* and use IL2CPP::Object() constructor
    */

    /*
    Getting info of methods
    */

    IL2CPP::Method *PixelTime_Update = AssemblyCSharp->Class("PixelTime")->Method("Update");
    uint64_t PixelTime_Update_VA = PixelTime_Update->VA();   // Value address
    uint64_t PixelTime_Update_RVA = PixelTime_Update->RVA(); // Relative value address (offset)
    const char *PixelTime_Update_Name = PixelTime_Update.Name();

    /*
    Strings
    */
    IL2CPP::String *String1 = IL2CPP::String::New("example");
    std::string String1_Content = String1->Content(); // also you can set content by SetContent() method
    int String1_Length = String1->Length();
    // if you want to string into parameter use String.Address()

    /*
    Arrays.
    For example i'll use array with classes (string)
    */
    IL2CPP::Array *String_Array = IL2CPP::Array::New(mscorlib.Class("System.String"), 3);
    void *String_Array_Elements = String_Array->Elements();                    // pointer to C-array of elements
    String_Array->Set(0, String1);                                             // set value
    IL2CPP::String String2 = (IL2CPP::String *)(String_Array->Get<void *>(0)); // getting string value
    int String_Array_Length = String_Array->Length();

    /*
    Nested classes
    */
    IL2CPP::Class *Nested_Klass = AssemblyCSharp->Class("Progress.丂丏丂丛丛业丐东与")->Nested("丞丁业丄丘东与丅不");
    const char *Nested_Klass_Name = Nested_Klass->Name(); // 丞丁业丄丘东与丅不
}
