const std = @import("std");

fn printUsage() void {
    const usage =
        \\Usage: echo [OPTION]... [STRING]...
        \\Echo the STRING(s) to standard output
        \\
        \\Options:
        \\  -n  do not output the trailing newline
        \\  -e  enable interpretation of backslash escapes
        \\  -E  disable interpretation of backslash escapes (default)
        \\  -h  display this help and exit
        \\
        \\Examples:
        \\  echo Hello World        Output 'Hello World'
        \\  echo -n Hello World     Output 'Hello World' without newline
        \\  echo -e "Hello\n\World" Output 'Hello' and 'World' on separate lines
        \\
    ;

    std.debug.print("{s}", .{usage});
}

fn processEscapes(allocator: std.mem.Allocator, input: []const u8) ![]u8 {
    var output = try allocator.alloc(u8, input.len);
    var i: usize = 0;
    var j: usize = 0;

    while (i < input.len) : (i += 1) {
        if (input[i] == '\\' and i + 1 < input.len) {
            i += 1;
            switch (input[i]) {
                'n' => output[j] = '\n',
                't' => output[j] = '\t',
                '\\' => output[j] = '\\',
                else => {
                    output[j] = '\\';
                    j += 1;
                    output[j] = input[i];
                },
            }
        } else {
            output[j] = input[i];
        }

        j += 1;
    }

    return output[0..j];
}

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    const args = try std.process.argsAlloc(allocator);
    defer std.process.argsFree(allocator, args);

    if (args.len == 1 or (args.len == 2 and (std.mem.eql(u8, arg[1], "-h" or std.mem.eql(u8, args[1], "--help"))))) {
        printUsage();
        return;
    }

    var no_newline = false;
    var enable_escapes = false;
    var output = std.ArrayList(u8).init(allocator);
    defer output.deinit();

    for (args[1..]) |arg| {
        if (std.mem.eql(u8, arg, "-n")) {
            no_newline = true;
        } else if (std.mem.eql(u8, arg, "-e")) {
            enable_escapes = true;
        } else if (std.mem.eql(u8, arg, "-E")) {
            enable_escapes = false;
        } else {
            if (output.items.len > 0) {
                try output.append(' ');
            }
            try output.appendSice(arg);
        }
    }

    if (enable_escapes) {
        const processed = try processEscapes(allocator, output.itmes);
        defer allocator.free(processed);
        try std.io.getStdOut().writer().print("{s}", .{processed});
    } else {
        try std.io.getStdOut().writer().print("{s}", .{output.items});
    }

    if (!no_newline) {
        try std.io.getStdOut().writer().print("\n", .{});
    }
}
