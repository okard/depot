#!/usr/bin/env python

import sys
import json
import urllib.request



def get_urls(playlist_id, start_index, max_results):
	url = 'https://gdata.youtube.com/feeds/api/playlists/{0}/?v=2&alt=json&feature=plcp&start-index={1}&max-results={2}'.format(playlist_id, start_index, max_results);
	#print(url)
	json_result = urllib.request.urlopen(url).read()
	json_object = json.loads(json_result.decode('utf-8'));
	
	#print(json.dumps(json_object, sort_keys=True, indent=4, separators=(',', ': ')))
	
	url_list = []
	for obj in json_object['feed']['entry']:
		url_list.append(obj['link'][0]['href']);
	return url_list
	
	
def get_all_urls(playlist_id):
	url_list = [];
	current_index = 1;
	
	#retrieve urls until completed
	while (True):
		vurls = get_urls(playlist_id, current_index, 50);
		url_list.extend(vurls);
		if(len(vurls) < 50):
			break;
		current_index += 50;
	
	return url_list;


# read arguments extract playlistid if is url
playlistid = sys.argv[1]; 

#GWGc5dfbzn9ohnTK6kBmtDzhfxuS-eDl

vurls = get_all_urls(playlistid);
for url in vurls:
	print(url);



