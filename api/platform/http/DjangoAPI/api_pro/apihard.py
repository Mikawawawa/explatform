import json
from django.http import HttpResponse




def get_pmessage(request):
    re = {
		'powerp':1,
		'powert':[
			{
				'row':1,
				'line':3
			},
			{
				'row':1,
				'line':3
			}
			],
		}
    return HttpResponse(json.dumps(re), content_type="application/json")

def get_emessage(request):
    re = {'class':16040315,'process':7}
    return HttpResponse(json.dumps(re), content_type="application/json")

def sign(request):
    re = {'code':1,'info':['operation1','operation2']}
    return HttpResponse(json.dumps(re), content_type="application/json")

def init(request):
    re = {'code':1}
    return HttpResponse(json.dumps(re), content_type="application/json")

def check_teacher(request):
    re = {'code':1}
    return HttpResponse(json.dumps(re), content_type="application/json")

def put_grade(request):
    re = {'code':1}
    return HttpResponse(json.dumps(re), content_type="application/json")



















