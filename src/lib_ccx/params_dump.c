#include "lib_ccx.h"
#include "ccx_common_option.h"

void params_dump(struct lib_ccx_ctx *ctx)
{
	// Display parsed parameters
	mprint ("Input: ");
	switch (ccx_options.input_source)
	{
		case CCX_DS_FILE:
			for (int i=0;i<ctx->num_input_files;i++)
				mprint ("%s%s",ctx->inputfile[i],i==(ctx->num_input_files-1)?"":",");
			break;
		case CCX_DS_STDIN:
			mprint ("stdin");
			break;
		case CCX_DS_NETWORK:
			if (ccx_options.udpaddr == NULL)
				mprint ("Network, UDP/%u",ccx_options.udpport);
			else
			{
				mprint ("Network, %s:%d",ccx_options.udpaddr, ccx_options.udpport);
			}
			break;
		case CCX_DS_TCP:
			mprint("Network, TCP/%s", ccx_options.tcpport);
			break;
	}
	mprint ("\n");
	mprint ("[Extract: %d] ", ccx_options.extract);
	mprint ("[Stream mode: ");

	ctx->demux_ctx->print_cfg(ctx->demux_ctx);
	mprint ("]\n");
	mprint ("[Program : ");
	if (ccx_options.demux_cfg.ts_forced_program_selected != 0)
		mprint ("%u ]",ccx_options.demux_cfg.ts_forced_program);
	else
		mprint ("Auto ]");
	mprint (" [Hauppage mode: %s]",ccx_options.hauppauge_mode?"Yes":"No");

	mprint (" [Use MythTV code: ");
	switch (ccx_options.auto_myth)
	{
		case 0:
			mprint ("Disabled");
			break;
		case 1:
			mprint ("Forced - Overrides stream mode setting");
			break;
		case 2:
			mprint ("Auto");
			break;
	}
	mprint ("]");
	if (ccx_options.wtvconvertfix)
	{
		mprint (" [Windows 7 wtv to dvr-ms conversion fix: Enabled]");
	}
	mprint ("\n");

	if (ccx_options.wtvmpeg2)
	{
		mprint (" [WTV use MPEG2 stream: Enabled]");
	}
	mprint ("\n");

	mprint ("[Timing mode: ");
	switch (ccx_options.use_gop_as_pts)
	{
		case 1:
			mprint ("GOP (forced)");
			break;
		case -1:
			mprint ("PTS (forced)");
			break;
		case 0:
			mprint ("Auto");
			break;
	}
	mprint ("] ");
	mprint ("[Debug: %s] ", (ccx_options.debug_mask & CCX_DMT_VERBOSE) ? "Yes": "No");
	mprint ("[Buffer input: %s]\n", ccx_options.buffer_input ? "Yes": "No");
	mprint ("[Use pic_order_cnt_lsb for H.264: %s] ", ccx_options.usepicorder ? "Yes": "No");
	mprint("[Print CC decoder traces: %s]\n", (ccx_options.debug_mask & CCX_DMT_DECODER_608) ? "Yes" : "No");
	mprint ("[Target format: %s] ",ctx->extension);
	mprint ("[Encoding: ");
	switch (ccx_options.encoding)
	{
		case CCX_ENC_UNICODE:
			mprint ("Unicode");
			break;
		case CCX_ENC_UTF_8:
			mprint ("UTF-8");
			break;
		case CCX_ENC_LATIN_1:
			mprint ("Latin-1");
			break;
	}
	mprint ("] ");
	mprint ("[Delay: %lld] ",ctx->subs_delay);

	mprint ("[Trim lines: %s]\n",ccx_options.trim_subs?"Yes":"No");
	mprint ("[Add font color data: %s] ", ccx_options.nofontcolor? "No" : "Yes");
	mprint ("[Add font typesetting: %s]\n", ccx_options.notypesetting? "No" : "Yes");
	mprint ("[Convert case: ");
	if (ccx_options.sentence_cap_file!=NULL)
		mprint ("Yes, using %s", ccx_options.sentence_cap_file);
	else
	{
		mprint ("%s",ccx_options.sentence_cap?"Yes, but only built-in words":"No");
	}
	mprint ("]");
	mprint (" [Video-edit join: %s]", ccx_options.binary_concat?"No":"Yes");
	mprint ("\n[Extraction start time: ");
	if (ccx_options.extraction_start.set==0)
		mprint ("not set (from start)");
	else
		mprint ("%02d:%02d:%02d", ccx_options.extraction_start.hh,
				ccx_options.extraction_start.mm,
				ccx_options.extraction_start.ss);
	mprint ("]\n");
	mprint ("[Extraction end time: ");
	if (ccx_options.extraction_end.set==0)
		mprint ("not set (to end)");
	else
		mprint ("%02d:%02d:%02d", ccx_options.extraction_end.hh,
				ccx_options.extraction_end.mm,
				ccx_options.extraction_end.ss);
	mprint ("]\n");
	mprint ("[Live stream: ");
	if (ccx_options.live_stream==0)
		mprint ("No");
	else
	{
		if (ccx_options.live_stream<1)
			mprint ("Yes, no timeout");
		else
			mprint ("Yes, timeout: %d seconds",ccx_options.live_stream);
	}
	mprint ("] [Clock frequency: %d]\n",MPEG_CLOCK_FREQ);
	mprint ("Teletext page: [");
	if (tlt_config.page)
		mprint ("%d]\n",tlt_config.page);
	else
		mprint ("Autodetect]\n");
	mprint ("Start credits text: [%s]\n",
			ccx_options.start_credits_text?ccx_options.start_credits_text:"None");
	if (ccx_options.start_credits_text)
	{
		mprint ("Start credits time: Insert between [%ld] and [%ld] seconds\n",
				(long) (ccx_options.startcreditsnotbefore.time_in_ms/1000),
				(long) (ccx_options.startcreditsnotafter.time_in_ms/1000)
		       );
		mprint ("                    Display for at least [%ld] and at most [%ld] seconds\n",
				(long) (ccx_options.startcreditsforatleast.time_in_ms/1000),
				(long) (ccx_options.startcreditsforatmost.time_in_ms/1000)
		       );
	}
	if (ccx_options.end_credits_text)
	{
		mprint ("End credits text: [%s]\n",
				ccx_options.end_credits_text?ccx_options.end_credits_text:"None");
		mprint ("                    Display for at least [%ld] and at most [%ld] seconds\n",
				(long) (ccx_options.endcreditsforatleast.time_in_ms/1000),
				(long) (ccx_options.endcreditsforatmost.time_in_ms/1000)
		       );
	}

}

void print_file_report(struct lib_ccx_ctx *ctx)
{
	struct lib_cc_decode *dec_ctx = NULL;
	enum ccx_stream_mode_enum stream_mode;
	dec_ctx = ctx->dec_ctx;
#define Y_N(cond) ((cond) ? "Yes" : "No")

	printf("File: ");
	switch (ccx_options.input_source)
	{
		case CCX_DS_FILE:
			if (ctx->current_file < 0)
			{
				printf("file is not openened yet\n");
				return;
			}

			printf("%s\n", ctx->inputfile[ctx->current_file]);
			break;
		case CCX_DS_STDIN:
			printf("stdin\n");
			break;
		case CCX_DS_TCP:
		case CCX_DS_NETWORK:
			printf("network\n");
			break;
	}

	ctx->demux_ctx->print_report(ctx->demux_ctx);
	stream_mode = ctx->demux_ctx->get_stream_mode(ctx->demux_ctx);

	if (ctx->dec_ctx->in_bufferdatatype == CCX_PES &&
			(stream_mode == CCX_SM_TRANSPORT ||
			 stream_mode == CCX_SM_PROGRAM ||
			 stream_mode == CCX_SM_ASF ||
			 stream_mode == CCX_SM_WTV))
	{
		printf("Width: %u\n", ctx->freport.width);
		printf("Height: %u\n", ctx->freport.height);
		printf("Aspect Ratio: %s\n", aspect_ratio_types[ctx->freport.aspect_ratio]);
		printf("Frame Rate: %s\n", framerates_types[ctx->freport.frame_rate]);
	}

	printf("EIA-608: %s\n", Y_N(dec_ctx->cc_stats[0] > 0 || dec_ctx->cc_stats[1] > 0));

	if (dec_ctx->cc_stats[0] > 0 || dec_ctx->cc_stats[1] > 0)
	{
		printf("XDS: %s\n", Y_N(ctx->freport.data_from_608->xds));

		printf("CC1: %s\n", Y_N(ctx->freport.data_from_608->cc_channels[0]));
		printf("CC2: %s\n", Y_N(ctx->freport.data_from_608->cc_channels[1]));
		printf("CC3: %s\n", Y_N(ctx->freport.data_from_608->cc_channels[2]));
		printf("CC4: %s\n", Y_N(ctx->freport.data_from_608->cc_channels[3]));
	}

	printf("CEA-708: %s\n", Y_N(dec_ctx->cc_stats[2] > 0 || dec_ctx->cc_stats[3] > 0));

	if (dec_ctx->cc_stats[2] > 0 || dec_ctx->cc_stats[3] > 0)
	{
		printf("Services: ");
		for (int i = 0; i < CCX_DECODERS_708_MAX_SERVICES; i++)
		{
			if (ctx->freport.data_from_708->services[i] == 0)
				continue;
			printf("%d ", i);
		}
		printf("\n");

		printf("Primary Language Present: %s\n", Y_N(ctx->freport.data_from_708->services[1]));

		printf("Secondary Language Present: %s\n", Y_N(ctx->freport.data_from_708->services[2]));
	}

	printf("MPEG-4 Timed Text: %s\n", Y_N(ctx->freport.mp4_cc_track_cnt));
	if (ctx->freport.mp4_cc_track_cnt) {
		printf("MPEG-4 Timed Text tracks count: %d\n", ctx->freport.mp4_cc_track_cnt);
	}

	memset(&ctx->freport, 0, sizeof (struct file_report));

#undef Y_N
}
