
from django.conf.urls import url
 
from .views import doc
from .views import platform

urlpatterns = [
    url('gateway/get_pmessage',platform.get_pmessage),
    url('gateway/get_emessage/',platform.get_emessage),
    url('dialing/sign',platform.sign),
    url('dialing/init',platform.init),
    url('dialing/check_teacher',platform.check_teacher),
    url('dialing/put_grade',platform.put_grade),
    url("doc",doc.index)
]
